#pragma once

#include "request.hpp"
#include "worker.hpp"
#include <queue>
namespace simq
{
class Resource
{
  public:
    Resource(Worker, std::size_t);

    void release(double);
    bool process(const Request &);

  private:
    Worker m_Worker;
    std::size_t m_MaxCapacity;
    std::priority_queue<double, std::deque<double>, std::greater<>>
        m_TimeStamps;
};
} // namespace simq
