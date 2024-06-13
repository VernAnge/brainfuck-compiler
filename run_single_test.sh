#!/bin/bash

# Compilation
gcc src/brainfuck.c -o brainfuck

./brainfuck "test/test_simple.bf" > "test/test_simple.out.tmp"

sed -i 's/[[:space:]]*$//' test/test_simple.out.tmp
sed -i 's/[[:space:]]*$//' test/test_simple.out

echo "Expected:"
cat "test/test_simple.out"
echo "Got:"
cat "test/test_simple.out.tmp"

# Compare the stripped output files using cmp
if cmp -s "test/test_simple.out.tmp" "test/test_simple.out"; then
    echo -e "\nTest passed."
else
    echo -e "\nTest failed."
fi

rm "test/test_simple.out.tmp"
