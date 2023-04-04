#!/bin/perl
use Cwd qw(cwd);
     
print "Current working directory: ", cwd, "\n";
print "Arguments: ", join(',', map { "'$_'" } @ARGV), "\n";
print "Environment variables\n";
print "$_=$ENV{$_}\n" for (keys %ENV);

my $dir = $ENV{DIRECTORY};

mkdir $dir unless -e $dir;
for my $name (split(/ /, shift)) {
    opendir(D, $dir) || die "Can't open directory $dir: $!\n";
    my @list = readdir(D);
    closedir(D);

    foreach my $f (@list) {
	print "\$f = $f\n";
    }
    
    die "\nUnable to create $dir/$name\n" unless open FILE, ">$dir/$name";
    print FILE "This is $name\n";
    close FILE;
}

my $time = `date`;
print "::set-output name=time::$time\n";
