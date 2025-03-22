#pragma once

#include "request.hpp"
namespace simq
{

#define __REQUEST_IMPL(idx)                                                    \
    class RequestT##idx : public Request                                       \
    {                                                                          \
      public:                                                                  \
        using Request::Request;                                                \
                                                                               \
        State handle_event(State) override;                                    \
        double time_distribution() const noexcept override;                    \
        double processing_time(Worker) const noexcept override;                \
    } // namespace simq

__REQUEST_IMPL(1);
__REQUEST_IMPL(2);
__REQUEST_IMPL(3);

} // namespace simq

#undef __REQUEST_IMPL
