#include "schedule.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include "basic_repeating_timer.h"


Schedule::Schedule() : m_service(), m_work(m_service)
{
    boost::thread(boost::bind(&boost::asio::io_service::run, &m_service));
}

Schedule::~Schedule()
{

}

void Schedule::addTimeout(int seconds, timeout_handler handler)
{
    boost::asio::repeating_timer* timer = new boost::asio::repeating_timer(m_service);
    timer->start(boost::posix_time::seconds(seconds), handler);
}
