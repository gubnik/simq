#include "constants.hpp"
#include "logger.hpp"
#include <cstdio>

#define DOSPEED

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
    std::snprintf(msg.data(), msg.size(), "[SEIZE] REQUEST %lu RESOURCE %lu\n",
                  req, res);
#else
    std::snprintf(msg.data(), msg.size(),
                  "%.8lf [SEIZE] REQUEST %lu RESOURCE %lu\n", stamp, req, res);
#endif
    log(stamp, msg);
}

void simq::SmallLogger::log_release (TimeUnit stamp, std::size_t res) noexcept
{
    MessageType msg;
#ifdef DOSPEED
    std::snprintf(msg.data(), msg.size(), "[RELEASE] RESOURCE %lu\n", res);
#else
    std::snprintf(msg.data(), msg.size(), "%.8lf [RELEASE] RESOURCE %lu\n",
                  stamp, res);
#endif
    log(stamp, msg);
}

void simq::SmallLogger::log_terminate (std::size_t req,
                                       std::size_t res) noexcept
{
    MessageType msg;
#ifdef DOSPEED
    std::snprintf(msg.data(), msg.size(),
                  "[TERMINATE] REQUEST %lu RESOURCE %lu\n", req, res);
#else
    std::snprintf(msg.data(), msg.size(),
                  "[TERMINATE] REQUEST %lu RESOURCE %lu\n", req, res);
#endif
    log(constants::MaxTime, msg);
}
