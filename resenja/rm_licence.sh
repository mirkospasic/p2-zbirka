#!/bin/bash

WC=`wc -l licence.txt | awk '{print $1 + 1;}'`

for f in $(find . -name '*.c' -or -name '*.h'); do
    tail -n +$WC $f > tmp
    mv tmp $f
done
