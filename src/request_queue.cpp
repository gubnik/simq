#include "request_queue.hpp"
#include "request.hpp"
#include "worker.hpp"

simq::RequestQueue::RequestQueue (std::size_t first_max, std::size_t second_max)
    : m_First(simq::Worker::First, first_max),
      m_Second(simq::Worker::Second, second_max)
{
}

void simq::RequestQueue::release (double timestamp)
{
    m_First.release(timestamp);
    m_Second.release(timestamp);
}

bool simq::RequestQueue::process (const simq::Request &req)
{
    release(req.timestamp());
    const bool firstQueueReply  = m_First.process(req);
    const bool secondQueueReply = m_Second.process(req);
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
