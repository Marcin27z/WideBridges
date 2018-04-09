#!/bin/bash

i=0
for file in ./in/*
do
    echo "test $i"
    ./mosty <$file >"./out/out$i"
    ./comparator "./out/out$i" "./correct/correct$i"
    i=$[i+1]
done
