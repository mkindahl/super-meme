#!/bin/sh -l

echo "Hello $1"
pwd
ls -lR
time=$(date)
echo "::set-output name=time::$time"
