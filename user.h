#ifndef USER_H
#define USER_H

#include <string>

struct User
{
    unsigned int uid;
 	bool can_leech;
 	unsigned long long downloaded;
 	unsigned long long uploaded;
};

#endif // USER_H
