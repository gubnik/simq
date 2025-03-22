#pragma once

#include "request.hpp"
#include "resource.hpp"
#include <cstddef>
#include <memory>

namespace simq
{

class RequestQueue
{
  public:
    RequestQueue(std::size_t, std::size_t);

    bool process(const std::unique_ptr<Request> &);

  private:
    simq::Resource m_First;
    simq::Resource m_Second;
};

} // namespace simq
