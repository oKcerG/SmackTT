#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <boost/asio/io_service.hpp>
#include "basic_repeating_timer.h"

class Schedule
{
    typedef void(*timeout_handler)(const boost::system::error_code&);
public:
    Schedule();
    boost::asio::repeating_timer* addTimeout(int seconds, timeout_handler handler); //give ownership of the timer to the caller, stops when deleted

private:
    boost::asio::io_service m_service;
    boost::asio::io_service::work m_work;
};

#endif // SCHEDULE_H
