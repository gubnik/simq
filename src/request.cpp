#include "request.hpp"
#include "constants.hpp"
#include "worker.hpp"

#include <random>

simq::Request simq::Request::random (double timestamp)
{
    static std::random_device _rd;
    static std::mt19937 _gen(_rd());
    static std::uniform_int_distribution<> _distr(0, 2);
    const size_t idx = _distr(_gen);
    return Request(static_cast<Type>(idx), timestamp);
}

double simq::Request::exp_distr (double median)
{
    static std::random_device _rd;
    static std::mt19937 _gen(_rd());
    std::exponential_distribution<> _distr(1 / median);
    return _distr(_gen);
}

simq::Request::Request (Type type, double timestamp)
    : m_Type(type), m_TimeStamp(timestamp)
{
}

double simq::Request::time_distribution () const noexcept
{
    return m_TimeStamp +
           exp_distr(simq::constants::time_distribution_table[static_cast<int>(
               m_Type)]);
}

double simq::Request::processing_time (simq::Worker worker) const noexcept
{
    double val =
        simq::constants::processing_times_table[static_cast<int>(m_Type)]
                                               [static_cast<int>(worker)];
    if (val < 0)
    {
        return val;
    }
    return m_TimeStamp + exp_distr(val);
}

double simq::Request::timestamp () const noexcept
{
    return m_TimeStamp;
}
