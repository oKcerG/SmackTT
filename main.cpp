#include "server.h"
#include "schedule.h"
#include <iostream>
#include <boost/bind.hpp>
#include <windows.h>

void salut(const boost::system::error_code&)
{
    std::cout << "salut" << std::endl;
}

int main()
{
    //Server server;
    Schedule schedule;
    boost::asio::repeating_timer* timer = schedule.addTimeout(1, salut);
    for (int i = 0;;++i)
    {
        std::cout << "hello" << std::endl;
        Sleep(2000);
        if (i == 3)
            delete timer;
    }

    return 0;
}



