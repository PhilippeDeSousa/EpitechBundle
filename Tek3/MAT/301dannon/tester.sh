#! /bin/bash

ok() {
    echo -e "\e[1;32mOK\e[0m";
}

ko() {
    echo -e "\e[1;31mKO\e[0m";
}

compile() {
    echo -en "compilation\t: "
    make > /dev/null
    if [ $? -eq 0 ]; then
        ok
    else
        ko
    fi
}

compare() {
    echo -en $1 "\t: "
    if [[ $($1) == $($2) ]]; then
        ok
    else
        ko
        diff <($1) <($2)
    fi
}

compile

compare "./301dannon -h" "cat results/help.txt"
compare "./301dannon inputs/01.txt" "cat results/01.txt"
compare "./301dannon inputs/02.txt" "cat results/02.txt"
