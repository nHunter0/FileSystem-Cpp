//FileSystem.cpp
#include <iostream>
#include <vector>
#include <fstream>

#include "FileSystem.h"
#include "Initailize.h"
#include "Login.h"
#include "System.h"
#include "md5.h"

using namespace std;

void FileSystem::run_system(){
    System system;
    system.set_data(username,clearance);
    system.display_menu();
    userinput = system.user_input();
    system.run_menu(userinput);
};

void FileSystem::login(){
    cout << endl << "Login" << endl;
    cout << string(20,'-') << endl;
    Login login;
    username = login.login_username();
    login.verify_username(username);
    password = login.login_password();
    login.verify_infomation();
    clearance = login.get_clearance();

    cout << endl <<"Loged in" << endl;
    cout << string(20,'-') << endl;
    run_system(); //run system once loged in
 };

void FileSystem::initialize(){
    cout << endl << "User Initialization" << endl;
    cout << string(20,'-') << endl;
    Initialize initialize;
    username = initialize.initialize_username();
    initialize.check_username(username); //check if username in salt.txt
    password = initialize.initialize_password();
    salt = initialize.initialize_salt();
    clearance = initialize.initialize_clearance();
    passSaltHash = create_passwordHash(salt,password);

    /*//Test display to see if initialization was successful
    cout << "username           : " << username<< endl;
    cout << "password           : " << password<< endl;
    cout << "clearance          : " << clearance<< endl;
    cout << "salt               : " << salt << endl;
    cout << "passwordSaltHash   : " << passSaltHash << endl;
    */

    //Appending infomation to txt files
    update_salt(username,salt);
    update_shadow(username,passSaltHash,clearance);

    cout << endl << "Initialization process completed successfully." << endl;
    cout << "Please now run FileSystem wihtout argument -i" << endl;
    //login(); //optionaly run login once user is initailized
};

void FileSystem::update_salt(string username, string salt){
    ofstream salt_out("salt.txt",ios::app); //ios::app allows to append to end of file
    salt_out << username << ':' << salt << '\n';
};

void FileSystem::update_shadow(string username, string passSaltHash, int clearance){
    ofstream shadow_out("shadow.txt",ios::app);
    shadow_out << username << ':' << passSaltHash << ':' << clearance << '\n';
};

string FileSystem::create_passwordHash(string salt, string password){
    string pass_salt = password+salt;
    //cout << "Passing md5 function " << pass_salt << endl; //Test print

    //passing function md5 function passowrd with salt
    passSaltHash = md5(pass_salt);
    return passSaltHash;
};
