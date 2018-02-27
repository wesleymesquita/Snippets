#!/usr/bin/perl


$max_len_k = -1;
$max_len_v = -1;

while (($lk, $lv) = each %ENV){
	
	if(length $lk > $max_len_k){
		$max_len_k = length $lk;
	}
	
	if(length $lv > $max_len_v){
		$max_len_v = length $lv;
	}
}


$max_len_k++;
$max_len_v++;
if($max_len_k > 40){
	$max_len_k = 40;
}

if($max_len_v > 40){
	$max_len_v = 40;
}
printf "-"x$max_len_k . " | ". "-"x $max_len_v. "\n";
printf "%${max_len_k}s | %${max_len_v}s\n", "key", "value";
printf "-"x$max_len_k . " | ". "-"x $max_len_v. "\n";
while(($k, $v) = each %ENV){
	printf "%${max_len_k}s | %${max_len_v}s\n", $k, $v;
}
printf "-"x$max_len_k . "|". "-"x $max_len_v. "\n";

