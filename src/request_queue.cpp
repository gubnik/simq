#include "request_queue.hpp"
#include "request.hpp"
#include "worker.hpp"
#include <cstddef>
#include <memory>

simq::RequestQueue::RequestQueue (std::size_t first_max, std::size_t second_max)
    : m_First(simq::Worker::First, first_max),
      m_Second(simq::Worker::Second, second_max)
{
}

bool simq::RequestQueue::process (const std::unique_ptr<simq::Request> &req_ptr)
{
    const bool firstQueueReply  = m_First.process(req_ptr);
    const bool secondQueueReply = m_Second.process(req_ptr);
    if (firstQueueReply)
    {
        return true;
    }
    if (secondQueueReply)
    {
        return true;
    }
    return false;
}
