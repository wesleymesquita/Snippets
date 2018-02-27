#!/usr/bin/perl

@names = qw / fred betty barney dino wilma pebbles bamm-bamm /;
chomp(@idxs = <STDIN>);
foreach $idx(@idxs){
	print $names[$idx-1]," ";
}
