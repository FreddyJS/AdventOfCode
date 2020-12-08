if [[ -f ./bin/hellomake ]];then
    echo "Do you want to compile? (y/*)"
    read str
    if [ "$str" = "y" ];then
        make
    fi
else
    make
fi
./bin/hellomake ejercicio3.txt
