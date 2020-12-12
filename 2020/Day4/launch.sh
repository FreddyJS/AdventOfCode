#!/bin/bash
if [[ -f ./bin/hellomake ]];then
    echo "Do you want to compile? (y/*)"
    read str
    if [ "$str" = "y" ];then
        make
    fi
else
    make
fi
rm obj/*.gc*
./bin/hellomake input.txt
