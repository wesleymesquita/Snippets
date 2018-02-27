#!/usr/bin/perl

print "input strings. hit C-D to end\n";
@lines = ();
while (<STDIN>){
	push @lines, $_;
}
print '-' x 20, "\n";
while($#lines >= 0){
	printf "%20s", pop @lines;
}



	

