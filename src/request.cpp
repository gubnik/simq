#include "request_types.hpp"
#include "state.hpp"

#include <iostream>
#include <memory>
#include <random>

simq::State simq::Request::handle_event (simq::State prev_state)
{
    return simq::State::Generate;
}

std::unique_ptr<simq::Request> simq::Request::random (double timestamp)
{
    static std::random_device _rd;
    static std::mt19937 _gen(_rd());
    static std::uniform_int_distribution<> _distr(0, 2);
    size_t idx = _distr(_gen);
    switch (idx)
    {
    case 0:
        return std::make_unique<simq::RequestT1>(timestamp);
    case 1:
        return std::make_unique<simq::RequestT2>(timestamp);
    case 2:
        return std::make_unique<simq::RequestT3>(timestamp);
    default:
        __builtin_unreachable();
    };
}

simq::Request::Request (double timestamp) : m_TimeStamp(timestamp)
{
}

double simq::Request::timestamp () const noexcept
{
    return m_TimeStamp;
}
