#pragma once

#include "core.hpp"
#include <queue>

namespace simq
{

class Request
{
  public:
    Request(std::size_t, TimeUnit) noexcept;
    Request(Request &&) noexcept;

  public:
    Request &operator=(Request &&) noexcept;

  public:
    TimeUnit timestamp() const noexcept;
    std::size_t type() const noexcept;
    static bool accepted(std::size_t, std::size_t) noexcept;
    bool accepted(std::size_t) const noexcept;
    TimeUnit interval_time() const noexcept;
    TimeUnit processing_time(std::size_t) const noexcept;

  private:
    std::size_t m_Type;
    TimeUnit m_TimeStamp;
};

struct RequestComparator
{
    bool operator()(const Request &req1, const Request &req2)
    {
        return req1.timestamp() > req2.timestamp();
    }
};

using QueueType =
    std::priority_queue<Request, std::vector<Request>, RequestComparator>;
} // namespace simq
