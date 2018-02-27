#!/usr/bin/perl
use 5.010;
sub greet {
	state @last;
	#print "this is the last list size == $#last", "\n";
	if($#last == -1){
		print "Hi $_[0]! You are the first one here!\n";
	} else {
		print "Hi $_[0]! I've seen: $last[0]";
		foreach(1..$#last){
			print " $last[$_]";
		}
		print "\n";
	}
	push @last, $_[0];
}

@test = qw { Fred Barney Wilma Fred };

foreach(@test){
	&greet($_);
}
		

