#!/usr/bin/perl
print "input ruler size:\n";
chomp($ruler_sz = <STDIN>);

print "input strings. hit C-D to end\n";
@lines = ();
while (<STDIN>){
	chomp($line = $_);
	push @lines, $line;
}
print '-' x $ruler_sz, "\n";
$i = 0;
while($i <= $#lines){
	printf "%${ruler_sz}s\n", $lines[$i];
	$i++;
}



	

