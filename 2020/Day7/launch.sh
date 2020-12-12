#!/bin/bash
if [[ -f ./bin/day7 ]];then
    echo "Do you want to compile? (y/*)"
    read str
    if [ "$str" = "y" ];then
        make
    fi
else
    make
fi
rm obj/*.gc*
./bin/day7 input.txt
