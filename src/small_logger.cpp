#include "constants.hpp"
#include "logger.hpp"
#include <cstdio>

// #define DOSPEED

simq::SmallLogger::SmallLogger (simq::Logger &logger) : m_Logger(logger)
{
    m_Events.reserve(constants::MaxTime / constants::ResourceTypes);
}

simq::SmallLogger::SmallLogger (const simq::SmallLogger &logger)
    : m_Logger(logger.m_Logger)
{
    m_Events = logger.m_Events;
}

simq::SmallLogger::~SmallLogger ()
{
    m_Logger.append(*this);
}

void simq::SmallLogger::log (double timestamp, MessageType msg) noexcept
{
    m_Events.emplace_back(timestamp, msg);
}

void simq::SmallLogger::log_seize (TimeUnit stamp, std::size_t req,
                                   std::size_t res) noexcept
{
    MessageType msg;
#ifdef DOSPEED
    std::snprintf(msg.data(), msg.size(), "[SZE] RES %lu REQ %lu\n", res, req);
#else
    std::snprintf(msg.data(), msg.size(), "%8.4e [SZE] RES %lu REQ %lu\n",
                  stamp, req, res);
#endif
    log(stamp, msg);
}

void simq::SmallLogger::log_release (TimeUnit stamp, std::size_t res) noexcept
{
    MessageType msg;
#ifdef DOSPEED
    std::snprintf(msg.data(), msg.size(), "[RLS] RES %lu\n", res);
#else
    std::snprintf(msg.data(), msg.size(), "%8.4e [RLS] RES %lu\n", stamp, res);
#endif
    log(stamp, msg);
}

void simq::SmallLogger::log_terminate (std::size_t req,
                                       std::size_t res) noexcept
{
    MessageType msg;
#ifdef DOSPEED
    std::snprintf(msg.data(), msg.size(), "[TRM] RES %lu REQ %lu\n", res, req);
#else
    std::snprintf(msg.data(), msg.size(),
                  "__OVERTIME__ [TRM] RES %lu REQ %lu\n", res, req);
#endif
    log(constants::MaxTime, msg);
}
