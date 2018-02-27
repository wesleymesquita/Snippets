#!/usr/bin/perl
print "Enter lines\n";
chomp(@lines = <STDIN>);
print "Enter style: (s) space or (n) new lines\n";
chomp($style = <STDIN>);
@lines = sort @lines;
foreach $line(@lines){
	if($style eq "s"){
		print "$line ";
	}
	else{
		print "$line \n";
	}
}			
