#pragma once

#include "logger.hpp"
#include "request.hpp"
#include <coroutine>
#include <cstddef>

namespace simq
{

class request_generator
{
  public:
    struct promise_type;

  public:
    using handle_t     = std::coroutine_handle<promise_type>;
    using product_type = simq::Request *;

  public:
    request_generator(handle_t p_Handle);

    ~request_generator();

    product_type operator()();

    operator bool();

  private:
    handle_t m_Handle;
};

struct request_generator::promise_type
{
    product_type value = nullptr;

    request_generator get_return_object();

    auto yield_value(product_type &&from);

    void return_void();

    auto initial_suspend() noexcept;

    auto final_suspend() noexcept;

    void unhandled_exception();
};

request_generator spawn_request_generator(double, std::size_t, std::size_t);
} // namespace simq
