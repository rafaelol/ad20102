#!/usr/bin/perl
use strict;
use warnings;
use ProgressBar::Stack;


my $nro_rodadas_inicial = 10;
my $nro_rodadas_max = 1500;
my $nro_rodadas;

my $tam_rodadas_inicial = 1000;
my $tam_rodadas_max = 30000;
my $tam_rodadas;

my $passo_nro_rodadas = 10;
my $passo_tam_rodadas = 1000;

my $t_transiente = 10000;

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
	
	$nro_rodadas = $nro_rodadas_inicial;
	
	@resultados = ();
	$minimo = 2000000000;
	
	my $prog = 0;
	init_progress(count => ($nro_rodadas_max/$passo_nro_rodadas) );
	
	while($nro_rodadas <= $nro_rodadas_max)
	{
		$tam_rodadas = $tam_rodadas_inicial;
		
		$prog++;

		while($tam_rodadas <= $tam_rodadas_max)
		{
			update_progress ($prog, "nro = $nro_rodadas e tam = $tam_rodadas");
			
			my $t = $tam_rodadas * $nro_rodadas;
			
			#Nao precisamos continuar aumentando o tamanho de rodadas.
			last if($t > $minimo);
			
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
				my $c = 0;
				while($c < $stress_qty)
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
					
					last if(intervalos_ok() == 0);
					
					$c++;
				}
				
				if($c == $stress_qty)
				{		
					if($t == $minimo)
					{
						push @resultados, {nro => $nro_rodadas, tam => $tam_rodadas};
					}
					elsif($t < $minimo)
					{
						@resultados = ();
						push @resultados, {nro => $nro_rodadas, tam => $tam_rodadas};
						$minimo = $t;
					}					
				}
			}
			
			$tam_rodadas += $passo_tam_rodadas;
		}
		
		$nro_rodadas += $passo_nro_rodadas;
	}
	
	update_progress (($nro_rodadas_max/$passo_nro_rodadas), "fim :)\n");
	print "Valor otimizado, FATOR = $minimo.\n";
	print "Com a(s) seguinte(s) opcao(oes):\n";
	foreach my $result (@resultados)
	{
		print "# de rodadas = $result->{nro} e tamanho das rodadas = $result->{tam}\n";
	}
	
	print "\n\n";
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