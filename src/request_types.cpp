#include "request_types.hpp"
#include "constants.hpp"
#include "state.hpp"
#include "worker.hpp"
#include <random>

simq::State simq::RequestT1::handle_event (simq::State prev_state)
{
    return simq::Request::handle_event(prev_state);
}

simq::State simq::RequestT2::handle_event (simq::State prev_state)
{
    return simq::Request::handle_event(prev_state);
}

simq::State simq::RequestT3::handle_event (simq::State prev_state)
{
    return simq::Request::handle_event(prev_state);
}

#define __REQUEST_IMPL_TIME_DISTR(idx, CONSTNAME)                              \
    double simq::RequestT##idx::time_distribution() const noexcept             \
    {                                                                          \
        static std::random_device _rd;                                         \
        static std::mt19937 _gen(_rd());                                       \
        static std::exponential_distribution<> _distr(1 /                      \
                                                      constants::CONSTNAME);   \
        return timestamp() + _distr(_gen);                                     \
    }

__REQUEST_IMPL_TIME_DISTR(1, R1)
__REQUEST_IMPL_TIME_DISTR(2, G1)
__REQUEST_IMPL_TIME_DISTR(3, B1)

#undef __REQUEST_IMPL_TIME_DISTR

#define __REQUEST_IMPL_PROC_TIME(IDX)                                          \
    double simq::RequestT##IDX::processing_time(simq::Worker worker)           \
        const noexcept                                                         \
    {                                                                          \
        static double val =                                                    \
            constants::R##IDX + constants::G##IDX + constants::B##IDX;         \
                                                                               \
        static std::random_device _rd;                                         \
        static std::mt19937 _gen(_rd());                                       \
        static std::exponential_distribution<> _distr(1 / val);                \
        const auto idx = static_cast<int>(worker);                             \
        if (idx != IDX - 1)                                                    \
            return -1;                                                         \
        return m_TimeStamp + val;                                              \
    }

__REQUEST_IMPL_PROC_TIME(1)
__REQUEST_IMPL_PROC_TIME(2)

double simq::RequestT3::processing_time (simq::Worker worker) const noexcept
{
    auto val =
        (worker == simq::Worker::First)
            ? constants::R3 + constants::G3 + constants::B3 + constants::G1
            : constants::R3 + constants::G3 + constants::B3 + constants::B1;
    return m_TimeStamp + val;
}

#undef __REQUEST_IMPL_PROC_TIM
