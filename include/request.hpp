#pragma once

#include "worker.hpp"

namespace simq
{

class Request
{
  public:
    enum class Type
    {
        First = 0,
        Second,
        Any
    };

  public:
    Request(Type, double);
    double timestamp() const noexcept;

  public:
    static Request random(double);
    static double exp_distr(double);

  public:
    double time_distribution() const noexcept;
    double processing_time(Worker) const noexcept;

  protected:
    Type m_Type;
    double m_TimeStamp;
};

} // namespace simq
