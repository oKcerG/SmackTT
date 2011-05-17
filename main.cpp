#include "server.h"
#include "schedule.h"
#include "windows.h"
#include <boost/bind.hpp>

struct Foo
{
    Foo (Schedule &schedule) : timer(schedule.addTimeout(1, boost::bind(&Foo::hello, this)))
    {
        std::cout << "created\n";
    }
    ~Foo()
    {
        std::cout << "destructed\n";
    }
    void hello()
    {
        std::cout << "hello" << std::endl;
    }
    std::unique_ptr<boost::asio::repeating_timer> timer;
};

int main()
{
    Schedule schedule;
    {
        Foo hi(schedule);
        Sleep(10000);
        std::cout << "release" << std::endl;
        //hi.timer.release();
        std::cout << "released" << std::endl;
    }
        Sleep(5000);
    return 0;
}



