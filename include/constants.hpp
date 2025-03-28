#pragma once

#include "core.hpp"
#include <array>
#include <cstddef>
#include <cwchar>

namespace simq::constants
{

constexpr std::size_t MaxTime = 1e+7;

constexpr TimeUnit R1 = 8;
constexpr TimeUnit G1 = 11;
constexpr TimeUnit B1 = 8;
constexpr TimeUnit R2 = 11;
constexpr TimeUnit G2 = 7;
constexpr TimeUnit B2 = 11;
constexpr TimeUnit R3 = 7;
constexpr TimeUnit G3 = 8;
constexpr TimeUnit B3 = 5;

constexpr std::size_t RequestTypes  = 3;
constexpr std::size_t ResourceTypes = 2;

constexpr std::array<TimeUnit, RequestTypes> distribution_times_table = {
    {R1, G1, B1}};

constexpr std::array<std::array<TimeUnit, ResourceTypes>, RequestTypes>
    processing_times_table = {{{R1 + G1 + B1, -1},
                               {-1, R2 + G2 + B2},
                               {R3 + G3 + B3 + R1, R3 + G3 + G3 + B1}}};

template <std::size_t request> consteval std::size_t time_coeff ()
{
    std::size_t retval = 0;
    for (std::size_t i = 0; i < ResourceTypes; ++i)
    {
        if (processing_times_table[request][i] > 0)
        {
            ++retval;
        }
    }
    return retval;
}

template <std::size_t request> consteval TimeUnit interval_time ()
{
    constexpr std::size_t coeff = time_coeff<request>();
    static_assert(coeff != 0, "Index out of bounds");
    return distribution_times_table[request] * coeff;
}

template <std::size_t... Requests>
consteval auto generate_interval_times_table (std::index_sequence<Requests...>)
{
    return std::array<TimeUnit, RequestTypes>{{{interval_time<Requests>()}...}};
}

constexpr auto interval_time_table =
    generate_interval_times_table(std::make_index_sequence<RequestTypes>{});

} // namespace simq::constants
