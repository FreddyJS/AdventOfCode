FILE=bin/hellomake
if [[ -f /home/sebas/Documentos/AdventOfCode/2020/Day4/Makefile ]];then
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
