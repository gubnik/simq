#pragma once

#include "logger.hpp"
#include "request.hpp"
#include "statistics.hpp"
#include <deque>
#include <queue>
#include <thread>
namespace simq
{
class Resource
{
  public:
    Resource(Logger &, std::size_t, std::size_t) noexcept;
    ~Resource() noexcept;

  private:
    void request_handler() noexcept;

  private:
    void process(Request &&req) noexcept;
    void release(TimeUnit) noexcept;

  private:
    std::size_t m_Id;
    std::size_t m_MaxCapacity;
    std::priority_queue<TimeUnit, std::vector<TimeUnit>, std::greater<>>
        m_TimeStamps;
    QueueType m_Generated;
    std::queue<Request, std::deque<Request>> m_Waiting;

  private:
    std::thread m_HandlerThread;
    SmallLogger m_Logger;
    Statistics m_Statistics;
};
} // namespace simq
