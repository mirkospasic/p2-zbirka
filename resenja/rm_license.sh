#!/bin/bash

WC=`wc -l license.txt | awk '{print $1;}'`
WC1=`wc -l license.txt | awk '{print $1 + 1;}'`

for f in $(find . -name '*.c' -or -name '*.h'); do
    OK=$(diff <(head -n $WC $f) license.txt)
    if [ "$OK" != "" ]; then
	continue
    fi
    tail -n +$WC1 $f > tmp
    mv tmp $f
done
