#include "request.hpp"
#include "constants.hpp"

#include <random>

simq::Request::Request (std::size_t type, TimeUnit timestamp) noexcept
    : m_Type(type), m_TimeStamp(timestamp)
{
}

simq::Request &simq::Request::operator=(Request &&req) noexcept
{
    if (this == &req)
    {
        return *this;
    }
    this->m_Type      = std::move(req.m_Type);
    this->m_TimeStamp = std::move(req.m_TimeStamp);
    return *this;
}

simq::Request::Request (Request &&req) noexcept
{
    this->m_Type      = std::move(req.m_Type);
    this->m_TimeStamp = std::move(req.m_TimeStamp);
}

bool simq::Request::accepted (std::size_t request, std::size_t worker) noexcept
{
    TimeUnit val = simq::constants::processing_times_table[request][worker];
    return val > 0;
}

bool simq::Request::accepted (std::size_t worker) const noexcept
{
    TimeUnit val = simq::constants::processing_times_table[m_Type][worker];
    return val > 0;
}

simq::TimeUnit simq::Request::interval_time () const noexcept
{
    TimeUnit val = simq::constants::interval_time_table[m_Type];
    static thread_local std::random_device _rd;
    static thread_local std::mt19937 _gen(_rd());
    std::exponential_distribution<> _distr(1 / val);
    return m_TimeStamp + _distr(_gen);
}

simq::TimeUnit
simq::Request::processing_time (std::size_t worker) const noexcept
{
    TimeUnit val = simq::constants::processing_times_table[m_Type][worker];
    static thread_local std::random_device _rd;
    static thread_local std::mt19937 _gen(_rd());
    std::exponential_distribution<> _distr(1 / val);
    return m_TimeStamp + _distr(_gen);
}

simq::TimeUnit simq::Request::timestamp () const noexcept
{
    return m_TimeStamp;
}

std::size_t simq::Request::type () const noexcept
{
    return m_Type;
}
