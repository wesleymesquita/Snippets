#!/usr/bin/perl
sub total {
	my($sum_total) = (0);
	foreach(@_){
		$sum_total += $_;
	}
	$sum_total;
}

sub ave {
	&total(@_)/$#_;
}

sub above_ave {
	my($avg) = &ave(@_);
	my @ret = ();
	foreach(@_){
		if($_> $avg){
			push @ret, $_;
		}
	}
	@ret	
}

my @fred = qw{ 1 3 5 7 9 };
print &total(@fred), "\n";

print &total(1..10), "\n";

print &ave(@fred), " -- ", &above_ave(@fred);
