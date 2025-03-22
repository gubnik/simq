#include "generator.hpp"
#include "request_queue.hpp"
void simq::spawn_request_generator (double max_time,
                                    std::size_t first_queue_size,
                                    std::size_t second_queue_size)
{
    double current_time = 0;
    simq::RequestQueue queue(first_queue_size, second_queue_size);
    while (current_time <= max_time)
    {
        auto req     = simq::Request::random(current_time);
        current_time = req.time_distribution();
        queue.process(req);
    }
}
