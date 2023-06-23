//Initailize.cpp
#include <string>
#include <random>
#include <fstream>
#include <sstream>

#include "Initailize.h"

using namespace std;

string Initialize::initialize_username(){
    cout << "Username: ";
    cin >> username;
    return username;
};

string Initialize::initialize_password(){
    string confirm_pass;
    cout << "Password: ";
    cin >> password;

    bool password_check = false;
    while( !password_check ){
        //Password checks:
        /*
            - password must contain 8 or more characters
            - password must contain at least one digit
        */
        if(password.size() >= 8){
            for(auto chars : password){
                if(isdigit(chars)){
                    password_check = true;
                }
            }
        }

        if(!password_check){
            cout << "Please try agin, make sure your password is at least 8 characters long and contains a digit." << endl;
            password = "";
            cout << "Password: ";
            cin >> password;
        }
    } //while end

    cout << "Confirm password: ";
    cin >> confirm_pass;

    if(password == confirm_pass){
        return password;
    }
    else {
        cout << "Password does not match" << endl;
        exit(0);
    }
};

int Initialize::initialize_clearance(){
    cout << "User clearance (0 or 1 or 2 or 3):";
    cin >> clearance;
    return clearance;
};

string Initialize::initialize_salt(){
    for(int i=0; i<8; i++){
        int random_number = rand()%10;
        salt += to_string(random_number);
    }
    return salt;
};

void Initialize::check_username(string username){
    string line;
    string file_username;
    string fileName = "salt.txt";
    fstream inFile(fileName);

    if(!inFile){
        cout << "Error opening file " << fileName << endl;
        exit(3);
    }

    while(getline(inFile,line)){
        stringstream ss(line);
        getline(ss, file_username, ':'); //reading until ':' to extract usernames from salt.txt

        /*//Display for all usernames in salt.txt
        cout << file_username << endl;*/

        if(file_username == username){
            cout << file_username << " was found in " << fileName << " please run FileSystem again without -i" << endl;
            exit(0);
        }
    }
};
