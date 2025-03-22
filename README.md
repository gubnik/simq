# simq, simple queue simulation

## Prerequisites
- C++20 compliant compiler
- CMake

## How to compile
1. `mkdir build`
2. `cd build`
3. `cmake ..`
4. `make`, or whatever backend you used

## Execution
This program simulates an M/M/c queue that has 2 types of servers and 3 types of requests.
1st and 2nd request types can only be handled by the corresponding server type, but the 3rd
type can be handled by either one.

The end result of the program are logs, by default pushed into standard output, and metrics
regarding system load.
