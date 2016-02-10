#!/bin/bash

WC=`wc -l license.txt | awk '{print $1;}'`

for f in $(find . -name '*.c' -or -name '*.h'); do
    OK=$(diff <(head -n $WC $f) license.txt)
    if [ "$OK" == "" ]; then
	continue
    fi
    cat license.txt $f > tmp
    mv tmp $f
done


