#!/bin/bash

make

for i in {1..10}
do
    echo "Running test${i}.txt"
    ./exe ./testes/tests/test${i}.txt ${i}
done