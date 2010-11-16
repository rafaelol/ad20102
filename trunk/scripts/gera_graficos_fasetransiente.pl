#!/usr/bin/perl
use warnings;
use strict;
use Chart::Clicker;
use Chart::Clicker::Data::Series;
use Chart::Clicker::Data::DataSet;
use Chart::Clicker::Renderer::Line;
use List::MoreUtils qw (apply);
#use Data::Dumper::Simple;

my $passo = 250;
my $quantidade_amostras = 100000/$passo;

#Gráficos a serem gerados:
gera_graficos({
	fila1 => 'FCFS',
	fila2 => 'FCFS',
	lambda => '0.1',
	mi => '1'});

gera_graficos({
	fila1 => 'LCFS',
	fila2 => 'LCFS',
	lambda => '0.1',
	mi => '1'});

gera_graficos({
	fila1 => 'FCFS',
	fila2 => 'FCFS',
	lambda => '0.2',
	mi => '1'});

gera_graficos({
	fila1 => 'LCFS',
	fila2 => 'LCFS',
	lambda => '0.2',
	mi => '1'});

gera_graficos({
	fila1 => 'FCFS',
	fila2 => 'FCFS',
	lambda => '0.3',
	mi => '1'});

gera_graficos({
	fila1 => 'LCFS',
	fila2 => 'LCFS',
	lambda => '0.3',
	mi => '1'});

gera_graficos({
	fila1 => 'FCFS',
	fila2 => 'FCFS',
	lambda => '0.4',
	mi => '1'});

gera_graficos({
	fila1 => 'LCFS',
	fila2 => 'LCFS',
	lambda => '0.4',
	mi => '1'});

gera_graficos({
	fila1 => 'FCFS',
	fila2 => 'FCFS',
	lambda => '0.45',
	mi => '1'});

gera_graficos({
	fila1 => 'LCFS',
	fila2 => 'LCFS',
	lambda => '0.45',
	mi => '1'});


#The magic is here :)
sub gera_graficos
{
	my $param = shift;
	
	my @names = ("input1", "input2", "input3", "input4", "input5");
	my $name;
	
	my $dados = {};
	my $cmdline = "../cmulator -1 $param->{'fila1'} -2 $param->{'fila2'} -l $param->{'lambda'} -u $param->{'mi'} -b > output";
	
	my $titulo = "Fila 1: $param->{'fila1'} Fila 2: $param->{'fila2'} Lambda: $param->{'lambda'} Mi: $param->{'mi'}";
	my $base_filename = $param->{'fila1'} . "_" . $param->{'fila2'} . "_lambda" . $param->{'lambda'} . "_mi" . $param->{'mi'};
	
	print "Executando o simulador e obtendo os resultados...";
	
	foreach $name (@names)
	{
		$dados->{$name} = {};
		run_and_get($name, $cmdline, $dados);
	
	}
	
	print "pronto!\n";
	print "Comecando a gerar os graficos...\n";
	
	print "Graficos da Fila 1:\n";
	gen_graph(\@names, 'W1', 'E[W1]', $titulo, $dados, $base_filename . "_EW1.png");
	gen_graph(\@names, 'VarW1', 'Var(W1)', $titulo, $dados, $base_filename . "_VarW1.png");
	gen_graph(\@names, 'T1', 'E[T1]', $titulo, $dados, $base_filename . "_ET1.png");
	gen_graph(\@names, 'Nq1', 'E[Nq1]', $titulo, $dados, $base_filename . "_ENq1.png");
	gen_graph(\@names, 'N1', 'E[N1]', $titulo, $dados, $base_filename . "_EN1.png");
	
	print "Graficos da Fila 2:\n";
	gen_graph(\@names, 'W2', 'E[W2]', $titulo, $dados, $base_filename . "_EW2.png");
	gen_graph(\@names, 'VarW2', 'Var(W2)', $titulo, $dados, $base_filename . "_VarW2.png");
	gen_graph(\@names, 'T2', 'E[T2]', $titulo, $dados, $base_filename . "_ET2.png");
	gen_graph(\@names, 'Nq2', 'E[Nq2]', $titulo, $dados, $base_filename . "_ENq2.png");
	gen_graph(\@names, 'N2', 'E[N2]', $titulo, $dados, $base_filename . "_EN2.png");
	
	print "Enjoy :)\n";
}



sub run_and_get
{
	my ($inputcode, $cmdline, $dados) = @_;
	my $file;
	
	$dados->{$inputcode} = {};
	
	#Don't do this at home:
	`$cmdline`;
	
	open($file, '<', 'output');
	
	
	while(<$file>)
	{
		chomp $_;
		
		read_content($inputcode, 'W1', $file, $dados) 	 if(/Fila 1 - E\[W\]/);
		read_content($inputcode, 'VarW1', $file, $dados) if(/Fila 1 - Var\(W\)/);
		read_content($inputcode, 'T1', $file, $dados) 	 if(/Fila 1 - E\[T\]/);
		read_content($inputcode, 'Nq1', $file, $dados) 	 if(/Fila 1 - E\[Nq\]/);
		read_content($inputcode, 'N1', $file, $dados) 	 if(/Fila 1 - E\[N\]/);
		
		read_content($inputcode, 'W2', $file, $dados) 	 if(/Fila 2 - E\[W\]/);
		read_content($inputcode, 'VarW2', $file, $dados) if(/Fila 2 - Var\(W\)/);
		read_content($inputcode, 'T2', $file, $dados) 	 if(/Fila 2 - E\[T\]/);
		read_content($inputcode, 'Nq2', $file, $dados) 	 if(/Fila 2 - E\[Nq\]/);
		read_content($inputcode, 'N2', $file, $dados) 	 if(/Fila 2 - E\[N\]/);
	}
	
	close($file); 
}

sub read_content
{
	my ($inputname, $name, $file, $dados) = @_;

	$dados->{$inputname}->{$name} = [];
	
	push @{$dados->{$inputname}->{$name}}, 0;
	
	foreach (1..$quantidade_amostras)
	{
		$_ = <$file>;
		chomp $_;
		push @{$dados->{$inputname}->{$name}}, $_;
	}	
}

sub gen_graph
{
	my ($inputnames, $attrcode, $attrname, $titulo, $dados, $filename) = @_;
	
	print "Gerando grafico $filename...";
	
	my $chart = Chart::Clicker->new(width => 1600, height => 1200, format => 'png');
	$chart->title->text($titulo);
	$chart->title->padding->bottom(5);
	
	my $context = $chart->get_context('default');
	
	my $dataset = Chart::Clicker::Data::DataSet->new;
	my $render = Chart::Clicker::Renderer::Line->new;
	$render->brush->width(1);
	
	my $count = 1;
	my $iname;
	
	foreach $iname (@{$inputnames})
	{
		$dataset->add_to_series(Chart::Clicker::Data::Series->new({
			keys => [apply {$_ *= $passo} (0..$quantidade_amostras) ],
			values => $dados->{$iname}->{$attrcode},
			name => "Amostragem $count",
		}));
		
		$count++;
	}
	
	$chart->add_to_datasets($dataset);
	$context->renderer($render);
	$context->range_axis->label($attrname);
	$context->range_axis->fudge_amount(.1);
	$context->range_axis->ticks(10);
	$context->domain_axis->label("Tamanho da Fase Transiente");
	$context->domain_axis->ticks(10);
	
	$chart->write_output($filename);
	
	print "pronto!\n";
}