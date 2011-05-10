#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <boost/asio/io_service.hpp>

class Schedule
{
    typedef void(*timeout_handler)(const boost::system::error_code&);
public:
    Schedule();
    ~Schedule();
    void addTimeout(int seconds, timeout_handler handler);

private:
    boost::asio::io_service m_service;
    boost::asio::io_service::work m_work;
};

#endif // SCHEDULE_H
