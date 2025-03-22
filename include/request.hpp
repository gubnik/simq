#pragma once

#include "state.hpp"
#include "worker.hpp"
#include <memory>

namespace simq
{

class Request
{
  public:
    Request(double);
    double timestamp() const noexcept;

  public:
    static std::unique_ptr<Request> random(double);

  public:
    virtual State handle_event(State);
    virtual double time_distribution() const noexcept     = 0;
    virtual double processing_time(Worker) const noexcept = 0;

  protected:
    double m_TimeStamp;
};

} // namespace simq
