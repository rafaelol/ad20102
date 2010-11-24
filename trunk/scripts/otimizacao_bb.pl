#!/usr/bin/perl
use strict;
use warnings;
use DateTime;
use DateTime::Format::Duration;

my $nro_rodadas_inicial = 10;
my $nro_rodadas_max = 1260;
my $nro_rodadas;

my $tam_rodadas_inicial = 100;
my $tam_rodadas_max = 20000;
my $tam_rodadas;

my $t_transiente;

my %h_transiente = ("0.1"  => "10000",
		    "0.2"  => "10000",
		    "0.3"  => "10000",
		    "0.4"  => "10000",
		    "0.45" => "50000");

my $stress_qty = 10;

#O tamanho dos ICs devem ser menores ou iguais a 9.5%
#Não utilizar 10, para permitir uma "folga" na variação estatística normal.
my $limite_ic = 8.5;

my @lambdas = ("0.1", "0.2", "0.3", "0.4", "0.45");
my @disciplinas = ("FCFS", "LCFS");

my $minimo;
my @resultados;

foreach my $disciplina (@disciplinas)
{
	foreach my $lambda (@lambdas)
	{
		$t_transiente = $h_transiente{$lambda};
		
		otimiza({
			filas => $disciplina,
			lambda => $lambda,
		});
	}
}


sub otimiza
{
	my $params = shift;
	
	print "Otimizando resultados para filas com disciplina $params->{filas} e lambda = $params->{lambda}.\n";

	my $dt_inicio = DateTime->now;

	@resultados = ();
	$minimo = 2000000000;
	
	my $nro_inicio = $nro_rodadas_inicial;
	my $nro_fim    = $nro_rodadas_max;
	my $nro_meio   = int ( ($nro_inicio + $nro_fim) / 2);
	
	my $anterior;
	my $total_anterior;
	my $rod_anterior;
	
	$nro_rodadas = $nro_meio;
	$anterior = $nro_meio;

	my $temp1 = DateTime->now;

	$rod_anterior = bs_rodadas($params);
	
	my $temp2 = DateTime->now;
	my $tempodiff = $temp2 - $temp1;
	
	
	$total_anterior = $rod_anterior;
	
	$total_anterior *= $nro_rodadas if ($total_anterior != -1);

	while($nro_inicio <= $nro_fim)
	{	
		$nro_meio = int (($nro_inicio + $nro_fim) / 2);
		$nro_rodadas = $nro_meio;
		
		my $novo_inicio = $nro_meio + 1;
		my $novo_fim = $nro_meio - 1;

		my $rod_esquerdo = -1;
		my $rod_direito = -1;

		my $total_esquerdo;
		my $total_direito;
		
		#Esquerdo:
		$nro_rodadas = int (($nro_inicio + $novo_fim) / 2);
		
		$rod_esquerdo = bs_rodadas($params) if($nro_inicio <= $novo_fim);

		$total_esquerdo = $rod_esquerdo;
		$total_esquerdo *= $nro_rodadas if ($total_esquerdo != -1);

		#Direito:
		$nro_rodadas = int (($novo_inicio + $nro_fim) / 2);
		
		#Só vamos calcular o nó direito se o mínimo possível dele for proveitoso...
		$rod_direito = bs_rodadas($params) if(($novo_inicio <= $nro_fim) and
						      (($total_anterior == -1) or ($nro_rodadas * $tam_rodadas_inicial < $total_anterior)) and
						      (($total_esquerdo == -1) or ($nro_rodadas * $tam_rodadas_inicial < $total_esquerdo)));
		
		$total_direito = $rod_direito;
		$total_direito *= $nro_rodadas if ($total_direito != -1);
		
		$nro_rodadas = $nro_meio;
		
		if(($total_esquerdo != -1)    and
		     (($total_anterior == -1) or ($total_esquerdo <= $total_anterior)) and
		     (($total_direito == -1)  or ($total_esquerdo <= $total_direito)))
		{
			$anterior = int (($nro_inicio + $novo_fim) / 2);
			$rod_anterior = $rod_esquerdo;
			$minimo = $total_anterior = $total_esquerdo;
			$nro_fim = $nro_meio - 1;
			@resultados = ();
			push @resultados, {nro => $anterior, tam => $rod_esquerdo};
		}
		elsif(($total_anterior != -1) and
		     (($total_esquerdo == -1) or ($total_anterior <= $total_esquerdo)) and
		     (($total_direito == -1)  or ($total_anterior <= $total_direito)))
		{
			$minimo = $total_anterior;
			@resultados = ();
			push @resultados, {nro => $anterior, tam => $rod_anterior};
			last;
		}
		elsif(($total_direito != -1)  and
		     (($total_anterior == -1) or ($total_direito <= $total_anterior)) and
		     (($total_esquerdo == -1) or ($total_direito <= $total_esquerdo)))
		{
			$anterior = (int (($novo_inicio + $nro_fim) / 2));
			$rod_anterior = $rod_direito;
			$minimo = $total_anterior = $total_direito;
			$nro_inicio = $nro_meio + 1;
			@resultados = ();
			push @resultados, {nro => $anterior, tam => $rod_direito};
		}
		else
		{
			$minimo = -1;
			@resultados = ();
			last;
		}
		
		#print "$minimo, $resultados[0]->{nro}, $resultados[0]->{tam}.\n";
	}
	
	print "Valor otimizado, FATOR = $minimo.\n";
	print "Com a(s) seguinte(s) opcao(oes):\n";
	foreach my $result (@resultados)
	{
		print "# de rodadas = $result->{nro} e tamanho das rodadas = $result->{tam}\n";
	}
	
	my $dt_fim = DateTime->now;
	my $dt_diff = $dt_fim - $dt_inicio;

	my $format = DateTime::Format::Duration->new(
			pattern => '%M minuto(s) e %S segundo(s)');

	my $tempo = $format->format_duration($dt_diff);

	print "Tempo do teste: $tempo.\n";

	
	print "\n\n";
}

sub bs_rodadas
{	
	my $params = shift;
		
	my $rod_inicio = $tam_rodadas_inicial;	
	my $rod_fim    = $tam_rodadas_max;
	my $rod_meio;
	
	my $otimo = -1;

	while($rod_inicio <= $rod_fim)
	{
		$rod_meio   = int (($rod_inicio + $rod_fim) / 2);
		$tam_rodadas = $rod_meio;

		#print "$nro_rodadas - $tam_rodadas\n";

		my $t = $tam_rodadas * $nro_rodadas;

		if(testa($params) == 1) #Ok, passou no teste, então podemos diminuir :)
		{
			$rod_fim = $rod_meio - 1;
			$otimo = $tam_rodadas;
		}
		elsif($t > $minimo) #O tamanho ja esta maior que o $minimo, então não adianta tentar aumentar =(
		{
			return $otimo;
		}
		else #Os parametros não foram suficientes, então precisamos de rodadas maiores =X
		{
			$rod_inicio = $rod_meio + 1;
		}
	}
	
	return $otimo;
}

sub testa
{
	my $params = shift;
			
	executa_simulador({
		nrod => $nro_rodadas,
		trod => $tam_rodadas,
		transiente => $t_transiente,
		fila1 => $params->{filas},
		fila2 => $params->{filas},
		lambda => $params->{lambda},
		mi => "1",
	});

	if(intervalos_ok() == 1)
	{
		#roda test de stress para confirmar
		foreach (1..$stress_qty)
		{
			executa_simulador({
				nrod => $nro_rodadas,
				trod => $tam_rodadas,
				transiente => $t_transiente,
				fila1 => $params->{filas},
				fila2 => $params->{filas},
				lambda => $params->{lambda},
				mi => "1",
			});
			
			return 0 if(intervalos_ok() == 0);
		}
		return 1;
	}
	
	return 0;
}
sub intervalos_ok
{
	my $file;
	
	open($file, "<", "output") or return 0;
	
	while(<$file>)
	{
		if(/\[(\d+\.\d+)%\]$/)
		{
			return 0 if($1 > $limite_ic);
		}
	}

	close($file);
	
	return 1;
}

sub executa_simulador
{
	my $param = shift;
	
	my $cmdline = "../cmulator -m batch -n $param->{'nrod'} -r $param->{'trod'} -t $param->{'transiente'} -1 $param->{'fila1'} -2 $param->{'fila2'} -l $param->{'lambda'} -u $param->{'mi'} -o > output";
	
	`$cmdline`;
}