#include "resource.hpp"
#include "logger.hpp"
#include "request.hpp"
#include "worker.hpp"

simq::Resource::Resource (simq::Worker worker, std::size_t max_size)
    : m_Worker(worker), m_MaxCapacity(max_size)
{
}

void simq::Resource::release (double timestamp)
{
    const auto &logger = Logger::global();
    while (m_TimeStamps.size() && m_TimeStamps.top() <= timestamp)
    {
        logger.log("Freed resource of type ", static_cast<int>(m_Worker),
                   " due to be processed at ", m_TimeStamps.top());
        m_TimeStamps.pop();
    }
}

bool simq::Resource::process (const Request &req)
{
    const double processed_timestamp = req.processing_time(m_Worker);
    if (processed_timestamp < 0)
    {
        return false;
    }
    const auto &logger = Logger::global();
    if (m_TimeStamps.size() >= m_MaxCapacity)
    {
        logger.log("Blocked request for resource of type ",
                   static_cast<int>(m_Worker), " at ", req.timestamp());
        return false;
    }
    logger.log("Seized resource of type ", static_cast<int>(m_Worker), " at ",
               req.timestamp());
    m_TimeStamps.push(processed_timestamp);
    return true;
}
