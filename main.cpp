#include "generator.hpp"
#include "logger.hpp"
int main (void)
{
    const simq::Logger &logger = simq::Logger::global();
    auto gen                   = simq::spawn_request_generator(100000, 1, 10);
    while (gen)
    {
        logger.log(gen()->timestamp());
    }
    return 0;
}
