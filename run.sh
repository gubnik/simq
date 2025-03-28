#/bin/bash

cd build
make
time ./main
wc -l logs.txt
