#!/usr/bin/perl
use 5.010;
%family = ();
$f_number = 1;
while($f_number <=3){
	say "Entry $f_number : First Name:";
	chomp($f_name = <STDIN>);
	say "Entry $f_number : Last Name:";
	chomp($l_name = <STDIN>);
	$family{$f_name} = $l_name;
	$f_number++;
}

while (($f,$l) = each %family){
	printf "First Name == $f and Last Name id $l\n";
}
