#!/usr/bin/perl
use strict;
use warnings;

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
	
	foreach (1..10000)
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
	}
	
	print "$sucessos de 10000 testes com sucesso.\n\n";
}
sub intervalos_ok
{
	my $file;
	my $limite_ic = 9.8;
	
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