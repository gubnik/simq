#include "generator.hpp"
#include "request_queue.hpp"
#include <cstddef>
#include <utility>

simq::request_generator::request_generator (handle_t p_Handle)
    : m_Handle(p_Handle)
{
}

simq::request_generator::~request_generator ()
{
    m_Handle.destroy();
}

simq::request_generator::product_type simq::request_generator::operator()()
{
    return std::move(m_Handle.promise().value);
}

simq::request_generator::operator bool()
{
    if (m_Handle)
    {
        m_Handle.resume();
        return !m_Handle.done();
    }
    return false;
}

simq::request_generator
simq::request_generator::promise_type::get_return_object ()
{
    return request_generator(handle_t::from_promise(*this));
}

auto simq::request_generator::promise_type::yield_value (
    simq::request_generator::product_type &&from)
{
    value = from;
    return std::suspend_always{};
}

void simq::request_generator::promise_type::return_void ()
{
}

auto simq::request_generator::promise_type::initial_suspend () noexcept
{
    return std::suspend_always{};
}

auto simq::request_generator::promise_type::final_suspend () noexcept
{
    return std::suspend_always{};
}

void simq::request_generator::promise_type::unhandled_exception ()
{
    std::exit(1);
}

simq::request_generator
simq::spawn_request_generator (double max_time, std::size_t first_queue_size,
                               std::size_t second_queue_size)
{
    double current_time = 0;
    simq::RequestQueue queue(first_queue_size, second_queue_size);
    while (current_time <= max_time)
    {
        auto req     = simq::Request::random(current_time);
        current_time = req->time_distribution();
        queue.process(req);
        co_yield req.release();
    }
}
