#include "resource.hpp"
#include "constants.hpp"
#include <utility>

simq::Resource::Resource (SmallLogger &&logger, std::size_t id,
                          std::size_t max_size) noexcept
    : m_Id(id), m_MaxCapacity(max_size),
      m_HandlerThread(&Resource::request_handler, this), m_Logger(logger)
{
}

simq::Resource::~Resource () noexcept
{
    m_HandlerThread.join();
    while (!m_Waiting.empty())
    {
        auto &&ref = m_Waiting.front();
        m_Logger.log_terminate(ref.type(), m_Id);
        m_Waiting.pop();
    }
}

void simq::Resource::request_handler () noexcept
{
    for (std::size_t i = 0; i < constants::RequestTypes; i++)
    {
        if (!Request::accepted(i, m_Id))
        {
            continue;
        }
        double current_time = 0;
        while (current_time < constants::MaxTime)
        {
            Request req(i, current_time);
            double timestamp = req.interval_time();
            current_time     = timestamp;
            m_Generated.emplace(std::move(req));
        }
    }
    while (!m_Generated.empty())
    {
        Request &&req = std::move(const_cast<Request &>(m_Generated.top()));
        m_Generated.pop();
        release(req.timestamp());
        process(std::move(req));
    }
}

void simq::Resource::release (TimeUnit timestamp) noexcept
{
    while (!m_TimeStamps.empty() && m_TimeStamps.top() <= timestamp)
    {
        m_Logger.log_release(m_TimeStamps.top(), m_Id);
        m_TimeStamps.pop();
    }
}

void simq::Resource::process (simq::Request &&req) noexcept
{
    m_Waiting.push(std::move(req));
    if (m_TimeStamps.size() >= m_MaxCapacity - 1)
    {
        return;
    }
    auto &&treq = m_Waiting.front();
    m_Waiting.pop();
    m_Logger.log_seize(treq.timestamp(), treq.type(), m_Id);
    m_TimeStamps.push(treq.processing_time(m_Id));
}
