#pragma once

#include "request.hpp"
#include "worker.hpp"
#include <cstddef>
#include <deque>
#include <functional>
#include <memory>
#include <queue>
namespace simq
{
class Resource
{
  public:
    Resource(Worker, std::size_t);

    bool process(const std::unique_ptr<Request> &);

  private:
    Worker m_Worker;
    std::size_t m_MaxCapacity;
    std::priority_queue<double, std::deque<double>, std::greater<>>
        m_TimeStamps;
};
} // namespace simq
