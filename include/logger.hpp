#pragma once

#include <concepts>
#include <condition_variable>
#include <mutex>
#include <ostream>
#include <queue>
#include <sstream>
#include <string>
#include <thread>

namespace simq
{

template <typename T>
concept IsStringConvertible = requires(T obj) {
    { std::to_string(obj) } -> std::convertible_to<std::string>;
} || requires(T obj) {
    { obj.str() } -> std::convertible_to<std::string>;
} || std::convertible_to<T, std::string>;

class Logger
{
  public:
    Logger(std::ostream &);

    ~Logger();

    template <IsStringConvertible... StrPack>
    void log (StrPack &&...vals) const noexcept
    {
        std::ostringstream oss;
        (void)std::initializer_list<int>{
            (oss << std::forward<StrPack>(vals), 0)...};
        std::lock_guard<std::mutex> lock(m_Mutex);
        m_LogQueue.push(oss.str());
        m_Condition.notify_one();
    }

    static const Logger &global();

  private:
    void process_queue();

  private:
    mutable std::mutex m_Mutex;
    mutable std::condition_variable m_Condition;
    std::thread m_Thread;
    std::atomic<bool> m_StopLoggingFlag;

  private:
    std::ostream &m_OutStream;
    mutable std::queue<std::string> m_LogQueue;
};

} // namespace simq
