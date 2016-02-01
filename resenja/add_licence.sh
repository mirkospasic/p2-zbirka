#!/bin/bash

for f in $(find . -name '*.c' -or -name '*.h'); do
    cat licence.txt $f > tmp
    mv tmp $f
done


