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
    schedule.addTimeout(1, salut);
    for (;;)
    {
        std::cout << "hello" << std::endl;
        Sleep(1000);
    }

    return 0;
}



