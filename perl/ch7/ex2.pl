#!/usr/bin/perl
use 5.010;

if($#ARGV != 0){
	die "Use ./ex1.pl [FileName]";
}
open my $file, '<', $ARGV[0]
	or die "invalid file name $ARGV[1]";

while( <$file> ){
	if(/(fred|Fred)/){
		print $_;
	}
}


