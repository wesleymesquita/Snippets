#!/usr/bin/perl

use 5.010;
say "Enter some words, please repeat some";
%words = ();
while(<STDIN>){
	chomp;
	if(exists $words{$_}){
		$words{$_}++;
	}else{
		$words{$_}=1;
	}
}

say "-" x 21;
printf "%10s|%10s\n", "word", "count";
say "-" x 21;

foreach $key (sort keys %words){
	printf "%10s|%10s\n", $key, $words{$key};
}

say "-" x 21;
