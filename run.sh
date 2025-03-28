#/bin/bash

cd build
make
time ./main > logs.txt
wc -l logs.txt
echo "Type 1 requests:"
grep --count "\[SEIZE\] REQUEST TYPE 0" logs.txt
echo "Type 2 requests:"
grep --count "\[SEIZE\] REQUEST TYPE 1" logs.txt
echo "Type 3 requests:"
grep --count "\[SEIZE\] REQUEST TYPE 2" logs.txt
