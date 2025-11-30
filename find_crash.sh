#!/bin/bash

for i in {1..1000}
do
    ./essai > t.txt
    ./essai_fap < t.txt
    if [ $? -ne 0 ]; then
        echo "CRASH FOUND on test $i!"
        break
    fi
done
