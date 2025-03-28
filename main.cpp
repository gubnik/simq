
#include "logger.hpp"
#include "resource_manager.hpp"
#include <fstream>
#include <ios>

int main (void)
{
    std::fstream file;
    file.open("logs.txt", std::ios::out);
    {
        simq::Logger logger(file);
        simq::ResourceManager<10, 10> manager(logger);
    }
    file.close();
    return 0;
}
