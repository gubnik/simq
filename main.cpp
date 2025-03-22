#include "generator.hpp"
int main (void)
{
    simq::spawn_request_generator(10000000, 100, 100);
    return 0;
}
