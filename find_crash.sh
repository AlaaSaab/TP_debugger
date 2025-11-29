#!/bin/bash

for i in {1..500}
do
    ./essai > t.txt
    ./essai_fap < t.txt
    if [ $? -ne 0 ]; then
        echo "CRASH FOUND on test $i!"
        break
    fi
done
