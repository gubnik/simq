#pragma once

#include "core.hpp"
#include <array>
#include <concepts>
#include <ostream>
#include <vector>

namespace simq
{

template <typename T>
concept IsStringConvertible = requires(T obj, std::ostream out) {
    { out << obj } -> std::convertible_to<std::ostream &>;
};

using MessageType = std::array<char, 64>;
class SmallLogger;

class Logger
{
    using Entry = std::pair<double, MessageType>;

  public:
    Logger(std::ostream &);

    ~Logger();

    void append(const SmallLogger &);
    static Logger &global() noexcept;

  private:
    std::ostream &m_OutStream;
    std::vector<Entry> m_Events;
};

class SmallLogger
{
    friend Logger;
    using Entry = std::pair<TimeUnit, MessageType>;

  public:
    SmallLogger(Logger &);
    SmallLogger(const SmallLogger &);
    ~SmallLogger();

  public:
    void log(double timestamp, MessageType msg) noexcept;
    void log_seize(TimeUnit stamp, std::size_t req, std::size_t res) noexcept;
    void log_release(TimeUnit stamp, std::size_t res) noexcept;
    void log_terminate(std::size_t req, std::size_t res) noexcept;

  private:
    Logger &m_Logger;
    std::vector<Entry> m_Events;
};

} // namespace simq
