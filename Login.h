#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED
#include <string>
class Login{
private:
    std::string username;
    std::string password;
    std::string passSaltHash;
    std::string salt;
    int clearance;
public:
    std::string login_username();
    std::string login_password();
    int get_clearance();
    void verify_infomation();
    void verify_username(std::string);
    bool verify_hash(std::string,std::string);
};//Login end
#endif // LOGIN_H_INCLUDED
