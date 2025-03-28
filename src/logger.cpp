#include "logger.hpp"
#include "constants.hpp"
#include <algorithm>
#include <cstring>
#include <execution>
#include <iostream>
#include <ostream>
#include <utility>

simq::Logger::Logger (std::ostream &p_OutStream) : m_OutStream(p_OutStream)
{
    m_Events.reserve(constants::MaxTime);
}

simq::Logger::~Logger ()
{
    std::sort(std::execution::par_unseq, m_Events.begin(), m_Events.end(),
              [] (const Entry &it1, const Entry &it2)
              { return it1.first < it2.first; });
    for (const auto &it : m_Events)
    {
        m_OutStream.write(it.second.data(), std::strlen(it.second.data()));
    }
}

void simq::Logger::append (const SmallLogger &logger)
{
    for (auto &&it : logger.m_Events)
    {
        m_Events.push_back(std::move(it));
    }
}

simq::Logger &simq::Logger::global () noexcept
{
    static Logger _logger(std::cout);
    return _logger;
}
