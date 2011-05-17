#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <boost/asio/io_service.hpp>
//#include <memory>
#include "basic_repeating_timer.h"

class Schedule
{
public:
    Schedule();
    std::unique_ptr<boost::asio::repeating_timer> addTimeout(int seconds, std::function<void (const boost::system::error_code&)> handler);

private:
    boost::asio::io_service m_service;
    boost::asio::io_service::work m_work;
};

#endif // SCHEDULE_H
