#include "resource.hpp"
#include "constants.hpp"
#include <utility>

simq::Resource::Resource (Logger &logger, std::size_t id,
                          std::size_t max_size) noexcept
    : m_Id(id), m_MaxCapacity(max_size),
      m_HandlerThread(&Resource::request_handler, this), m_Logger(logger),
      m_Statistics(id)
{
}

simq::Resource::~Resource () noexcept
{
    m_HandlerThread.join();
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
            m_Statistics.request(i);
            double timestamp = req.interval_time();
            current_time += timestamp;
            m_Generated.emplace(std::move(req));
        }
    }
    while (!m_Generated.empty())
    {
        Request req = std::move(const_cast<Request &>(m_Generated.top()));
        m_Generated.pop();
        release(req.timestamp());
        process(std::move(req));
        m_Statistics.load((double)m_TimeStamps.size() / (double)m_MaxCapacity);
    }
    while (!m_Waiting.empty())
    {
        m_Logger.log_terminate(m_Waiting.front().type(), m_Id);
        m_Waiting.pop();
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
    m_Statistics.queue_length(m_Waiting.size());
    if (m_TimeStamps.size() >= m_MaxCapacity)
    {
        m_Logger.log_enqueue(req.timestamp(), req.type(), m_Id);
        m_Waiting.push(std::move(req));
        return;
    }
    while (!m_Waiting.empty() && m_TimeStamps.size() < m_MaxCapacity)
    {
        auto &freq     = m_Waiting.front();
        auto true_time = freq.processing_time(m_Id) + req.timestamp();
        m_Logger.log_dequeue(req.timestamp(), req.type(), m_Id);
        m_Logger.log_seize(req.timestamp(), req.type(), m_Id);
        m_TimeStamps.push(true_time);
        m_Waiting.pop();
    }
    if (m_TimeStamps.size() >= m_MaxCapacity)
    {
        return;
    }
    m_Logger.log_seize(req.timestamp(), req.type(), m_Id);
    m_TimeStamps.push(req.timestamp() + req.processing_time(m_Id));
}
