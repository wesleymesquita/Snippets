#!/usr/bin/perl
chomp($r = <STDIN>);
if($r < 0){
	$r = 0;
}
$c = 2*3.141592654*$r;
print "Circ = $c\n";


