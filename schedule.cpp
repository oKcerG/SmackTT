#include "schedule.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>


Schedule::Schedule() : m_service(), m_work(m_service)
{
    boost::thread(boost::bind(&boost::asio::io_service::run, &m_service)); //run io_service in a thread and detach it
}

std::unique_ptr<boost::asio::repeating_timer> Schedule::addTimeout(int seconds, std::function<void (const boost::system::error_code&)> handler)
{
    std::unique_ptr<boost::asio::repeating_timer> timer(new boost::asio::repeating_timer(m_service));
    timer->start(boost::posix_time::seconds(seconds), handler);
    return timer;
}


