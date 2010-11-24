#!/usr/bin/perl
use strict;
use warnings;
use ProgressBar::Stack;

my @seedsfalhos = ();
my $maior_ic = "0";

testa({
	nro 		=> 490,
	tam 		=> 720,
	transiente 	=> 10000,
	filas 		=> 'FCFS',
	lambda 		=> '0.1'
});

testa({
	nro 		=> 640,
	tam 		=> 770,
	transiente 	=> 10000,
	filas 		=> 'FCFS',
	lambda 		=> '0.2'
});

testa({
	nro 		=> 950,
	tam 		=> 940,
	transiente 	=> 10000,
	filas 		=> 'FCFS',
	lambda 		=> '0.3'
});

testa({
	nro 		=> 640,
	tam 		=> 4100,
	transiente 	=> 10000,
	filas 		=> 'FCFS',
	lambda 		=> '0.4'
});

testa({
	nro 		=> 1110,
	tam 		=> 8360,
	transiente 	=> 50000,
	filas 		=> 'FCFS',
	lambda 		=> '0.45'
});

testa({
	nro 		=> 320,
	tam 		=> 1240,
	transiente 	=> 10000,
	filas 		=> 'LCFS',
	lambda 		=> '0.1'
});

testa({
	nro 		=> 640,
	tam 		=> 960,
	transiente 	=> 10000,
	filas 		=> 'LCFS',
	lambda 		=> '0.2'
});

testa({
	nro 		=> 950,
	tam 		=> 1260,
	transiente 	=> 10000,
	filas 		=> 'LCFS',
	lambda 		=> '0.3'
});

testa({
	nro 		=> 640,
	tam 		=> 7300,
	transiente 	=> 10000,
	filas 		=> 'LCFS',
	lambda 		=> '0.4'
});

testa({
	nro 		=> 950,
	tam 		=> 18700,
	transiente 	=> 50000,
	filas 		=> 'LCFS',
	lambda 		=> '0.45'
});

sub testa
{
	my $params = shift;
	
	my $sucessos = 0;
	my $fator = $params->{transiente} + ($params->{nro} * $params->{tam});
	
	print "Stress Test para $params->{filas}, lambda = $params->{lambda}\n";
	print "\tNumero de rodadas: $params->{nro}\n";
	print "\tTamanho das rodadas: $params->{tam}\n";
	print "\tFase transiente: $params->{transiente}\n";
	print "\tFATOR = $fator\n\n";
	
	init_progress;
	
	foreach my $round (1..10000)
	{
		executa_simulador({
			nrod => $params->{nro},
			trod => $params->{tam},
			transiente => $params->{transiente},
			fila1 => $params->{filas},
			fila2 => $params->{filas},
			lambda => $params->{lambda},
			mi => "1",
		});
	
		$sucessos++ if(intervalos_ok() == 1);
		
		update_progress ((($round/10000) * 100), "$round de 10000 ($sucessos ok) (maior falha = $maior_ic%)");
	}
	
	my $porc = ($sucessos/10000) * 100;
	
	print "$porc% testes com sucesso.\n";
	print scalar(@seedsfalhos) . "testes falharam, com as seguintes seeds:\n";
	foreach my $s (@seedsfalhos)
	{
		print "\t-c $s->{chegada} -x $s->{servico} (ic alto = $s->{ic}%)\n";
	}
	
	print "\n\n";
}
sub intervalos_ok
{
	my $file;
	my $limite_ic = 9.8;

	my $ops = 0;
	my $c;
	my $x;
	
	open($file, "<", "output") or return 0;
	
	while(<$file>)
	{
		if(/\[(\d+\.\d+)%\]$/)
		{
			$ops = $1 if ($1 > $limite_ic and $1 > $ops);
		}
		
		if(/-c (\d+) -x (\d+)$/)
		{
			$c = $1;
			$x = $2;
		}
	}

	close($file);

	if($ops > $limite_ic)
	{
		$maior_ic = $ops if($ops > $maior_ic);
		push @seedsfalhos, {chegada => $c, servico => $x, ic => $ops};
		return 0;
	}
	
	return 1;
}

sub executa_simulador
{
	my $param = shift;
	
	my $cmdline = "../cmulator -m batch -n $param->{'nrod'} -r $param->{'trod'} -t $param->{'transiente'} -1 $param->{'fila1'} -2 $param->{'fila2'} -l $param->{'lambda'} -u $param->{'mi'} -o > output";
	
	`$cmdline`;
}