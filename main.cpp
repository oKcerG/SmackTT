#include "server.h"
#include <deque>
enum Test
{
    tocard,
    bonjour,
    aurevoir,
    pouet
};

template <typename T>
std::deque<T>& operator<<(std::deque<T>& deque, const T& value)
{
    deque.push_back(value);
    return deque;
}

int main()
{
    std::deque<std::wstring> d;
    d << "coucou" << "xianta";
    Server server;
    server.run();
    return 0;
}



