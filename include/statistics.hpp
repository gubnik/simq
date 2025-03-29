#include "constants.hpp"
#include <array>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>
namespace simq
{

class Statistics
{
  public:
    Statistics (std::size_t res_id) noexcept : m_Id(res_id)
    {
    }

    ~Statistics () noexcept
    {
        std::cout << "AT RESOURCE " << m_Id << "\n\t";
        for (std::size_t i = 0; i < m_RequestCounters.size(); i++)
        {
            std::cout << m_RequestCounters[i] << " TYPE " << i + 1
                      << " REQUESTS"
                      << "\n\t";
        }
        const double load =
            ((double)std::accumulate(m_Loads.begin(), m_Loads.end(), 0) /
             m_Loads.size());
        std::cout << "AVERAGE LOAD: " << load << "\n\t";
        long double qlen = 0;
        for (const auto &it : m_QueueLength)
        {
            qlen += (long double)it / m_QueueLength.size();
        }
        std::cout << "AVERAGE QUEUE LENGTH: " << (size_t)qlen << "\n";
    }

  public:
    void request (std::size_t type) noexcept
    {
        m_RequestCounters[type] += 1;
    }

    void load (double current_load) noexcept
    {
        m_Loads.push_back(current_load);
    }

    void queue_length (std::size_t length) noexcept
    {
        m_QueueLength.push_back(length);
    }

  private:
    std::size_t m_Id;
    std::array<std::size_t, constants::RequestTypes> m_RequestCounters = {{0}};
    std::vector<double> m_Loads;
    std::vector<std::size_t> m_QueueLength;
};

} // namespace simq
