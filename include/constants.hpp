#pragma once

#include <array>
namespace simq::constants
{

constexpr double R1 = 8;
constexpr double G1 = 11;
constexpr double B1 = 8;
constexpr double R2 = 11;
constexpr double G2 = 7;
constexpr double B2 = 11;
constexpr double R3 = 7;
constexpr double G3 = 8;
constexpr double B3 = 5;

constexpr std::array<double, 3> time_distribution_table = {{R1, G1, B1}};

constexpr std::array<std::array<double, 2>, 3> processing_times_table = {
    {{R1 + G1 + B1, -1},
     {-1, R2 + G2 + B2},
     {R3 + G3 + B3 + R1, R3 + G3 + G3 + B1}}};

} // namespace simq::constants
