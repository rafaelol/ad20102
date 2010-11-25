#!/usr/bin/perl

calc(0.1);
calc(0.2);
calc(0.3);
calc(0.4);
calc(0.45);

sub calc
{
	my $lambda = shift;
	
	my $W1 = (2 * $lambda)/(1 - $lambda);
	my $T1 = ($lambda + 1)/(1 - $lambda);
	
	my $W2 = (2 * $lambda * $lambda + 2 * $lambda)/(1 - 3 * $lambda + 2 * $lambda * $lambda);
	my $T2 = (4 * $lambda * $lambda - $lambda + 1)/(1 - 3 * $lambda + 2 * $lambda * $lambda);
	
	my $Nq1 = (2 * $lambda * $lambda)/(1 - $lambda);
	my $N1  = ($lambda * $lambda + $lambda)/(1-$lambda);
	
	my $Nq2 = (2 * $lambda * $lambda * $lambda + 2 * $lambda * $lambda)/(1 - 3 * $lambda + 2 * $lambda * $lambda);
	my $N2  = (4 * $lambda * $lambda * $lambda - $lambda * $lambda + $lambda)/(1 - 3 * $lambda + 2 * $lambda * $lambda);
	
	my $VarW1_LCFS = (4 * $lambda - 4 * $lambda * $lambda + 4 * $lambda * $lambda * $lambda)/((1 - $lambda) * (1 - $lambda) * (1 - $lambda));
	my $VarW1_FCFS = (8 * $lambda)/(2 - 2 * $lambda);
	
	print "Valoes analíticos para lambda = $lambda:\n";
	
	print "W1  = $W1\n";
	print "T1  = $T1\n";
	print "Nq1 = $Nq1\n";
	print "N1  = $N1\n";

	print "W2  = $W2\n";
	print "T2  = $T2\n";
	print "Nq2 = $Nq2\n";
	print "N2  = $N2\n";	
	
	print "VarW1 para LCFS = $VarW1_LCFS\n";
	print "VarW1 para FCFS = $VarW1_FCFS\n";
	
	print "\n\n";
}