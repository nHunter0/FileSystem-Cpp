#ifndef FILESYSTEM_H_INCLUDED
#define FILESYSTEM_H_INCLUDED
#include <iostream>

class FileSystem {
private:
    std::string username;
    std::string password;
    std::string passSaltHash;
    std::string salt;
    int clearance;
    std::string userinput;
public:
    void login();
    void initialize();
    void run_system();
    void update_salt(std::string,std::string);
    void update_shadow(std::string, std::string, int);
    std::string create_passwordHash(std::string,std::string);
};//FileSystem end

#endif // FILESYSTEM_H_INCLUDED
