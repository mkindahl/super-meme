#!/bin/perl
use Cwd qw(cwd);
     
print "Current working directory: ", cwd, "\n";
print "Arguments @ARGV\n";
print "Environment variables\n";
print "$_=$ENV{$_}\n" for (keys %ENV);

my $dir = $ENV{DIRECTORY};

for my $name (split(/ /, shift)) {
    die "\nUnable to create $dir/$name\n" unless open FILE, ">$dir/$name";
    print FILE "This is $name\n";
    close FILE;
}

my $time = `date`;
print "::set-output name=time::$time\n";
