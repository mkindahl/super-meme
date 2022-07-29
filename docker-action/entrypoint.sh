#!/bin/sh -l

set -x

echo "Arguments $@"
( mkdir $DIRECTORY && cd $DIRECTORY && touch "$@" )
env
pwd
ls -lR
time=$(date)
echo "::set-output name=time::$time"
