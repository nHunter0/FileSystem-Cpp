#ifndef INITAILIZE__H_INCLUDED
#define INITAILIZE__H_INCLUDED
#include <iostream>
#include <string>
class Initialize{
private:
    std::string username;
    std::string password;
    std::string passSaltHash;
    std::string salt;
    int clearance;
public:
    std::string initialize_username();
    std::string initialize_password();
    std::string initialize_salt();
    int initialize_clearance();
    void check_username(std::string);
};//Initialize end

#endif // INITAILIZE__H_INCLUDED
