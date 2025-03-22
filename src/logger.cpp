#include "logger.hpp"
#include <iostream>
#include <mutex>
#include <ostream>

simq::Logger::Logger (std::ostream &p_OutStream)
    : m_Thread(&Logger::process_queue, this), m_StopLoggingFlag(false),
      m_OutStream(p_OutStream)
{
}

simq::Logger::~Logger ()
{
    m_StopLoggingFlag = true;
    m_Condition.notify_all();
    {
        m_Thread.join();
    }
}

void simq::Logger::process_queue ()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(m_Mutex);
        m_Condition.wait(
            lock,
            [this] { return m_StopLoggingFlag || m_LogQueue.size() >= 100; });
        if (m_StopLoggingFlag && m_LogQueue.empty())
        {
            break;
        }
        while (!m_LogQueue.empty())
        {
            m_OutStream << m_LogQueue.front() << '\n';
            m_LogQueue.pop();
        }
    }
}

const simq::Logger &simq::Logger::global ()
{
    static simq::Logger logger(std::cout);
    return logger;
}
