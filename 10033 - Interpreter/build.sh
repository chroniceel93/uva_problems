#!/bin/bash
SOURCE="interpreter.cpp"
TIME=10
rm -rf vgcore*
# build the program w/ UVA flags
g++ -lm -lcrypt -O2 -ggdb -std=c++11 -pipe -DONLINE_JUDGE -Wall $SOURCE.cpp
RET=$?
if [[ $RET -eq 0 ]]
then
    g++ -lm -lcrypt -O0 -ggdb -std=c++11 -pipe -DONLINE_JUDGE $SOURCE.cpp -o $SOURCE
    # We take a given text.txt holding our test input, and save the result to output.txt
    time timeout $TIME ./a.out < text.txt > output.txt
    #if using vscode, this will automatically open a diff between the generated output, and a known-correct output.
    #code --diff output.txt accepted.txt
    #test the program for memory leaks. If the return code is anything but zero, then we run a more thorough check, and save the output to a text file.
    valgrind -q --error-exitcode=1 time timeout $TIME ./a.out < text.txt >& /dev/null
    RET=$?
    if [[ $RET -ne 0 ]]
    then
        valgrind --log-file=valgrind.txt -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./$SOURCE < text.txt > /dev/null
    fi
fi

