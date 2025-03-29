#/bin/bash

cd build
make
time ./main
wc -l logs.txt
echo "Type 1 requests:"
grep --count -E "\[SZE\] RES [0-9]+ REQ 0$" logs.txt
echo "Type 2 requests:"
grep --count -E "\[SZE\] RES [0-9]+ REQ 1$" logs.txt
echo "Type 3 requests:"
grep --count -E "\[SZE\] RES [0-9]+ REQ 2$" logs.txt
echo "Terminated in resources 0:"
grep --count -E "\[TRM\] RES 0" logs.txt
echo "Terminated in resources 1:"
grep --count -E "\[TRM\] RES 1" logs.txt
