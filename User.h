#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

struct User {
    int id;
    string username;
    string password;
    string role; // "admin" or "user"

    User() : id(0), username(""), password(""), role("user") {}
    User(int uId, string uName, string uPass, string uRole)
        : id(uId), username(uName), password(uPass), role(uRole) {}
};

#endif