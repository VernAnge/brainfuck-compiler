#!/bin/bash

# Compilation
gcc src/brainfuck.c -o brainfuck

# Test files
tests=("test1" "test2" "test3" "test4" "test5" "test6" "test7" "test8" "test9" "test10")

# Run tests
for test in "${tests[@]}"; do
    ./brainfuck "test/${test}.bf" > "test/${test}.out.tmp"
    if cmp -s "test/${test}.out.tmp" "test/${test}.out"; then
        echo "${test} passed."
    else
        echo -e "\n${test} failed."

        echo -e "\nExpected:"
        cat "test/${test}.out"
        echo -e "\nGot:"
        cat "test/${test}.out.tmp"
    fi
    rm "test/${test}.out.tmp"
done
