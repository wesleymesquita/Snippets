#!/usr/bin/perl
use 5.010;
sub greet {
	state $last = ""; 
	if($last eq ""){
		print "Hi $_[0]! You are the first one here!\n";
	} else {
		print "Hi $_[0]! $last is also here!\n";
	}
	$last = $_[0];
}

@test = qw { Fred Barney Wilma Fred };

foreach(@test){
	&greet($_);
}
		

