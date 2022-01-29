#!/bin/bash

make

for i in {1..9}
do
    echo "Running test${i}.txt"
    ./iterative_exe ./testes/test${i}.txt ${i}
done