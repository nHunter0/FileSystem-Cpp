//Login.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include "Login.h"
#include "FileSystem.h"

using namespace std;

string Login::login_username(){
    cout << "Username: ";
    cin >> username;
    return username;
};

string Login::login_password(){
    cout << "Password: ";
    cin >> password;
    return password;
};

void Login::verify_infomation(){
    FileSystem run;

    cout << endl;
    cout << username << " found in salt.txt" << endl;
    cout << "salt retrived: " << salt << endl;
    cout << "hashing..." << endl;
    string hash_value = run.create_passwordHash(salt,password);
    cout << "hash value: " << hash_value << endl;

    //Comparing the PassSaltHash value with that in the file shadow.txt
    if(!verify_hash(hash_value,username)){
        exit(3);
    }

    if(verify_hash(hash_value,username)){
        cout << "Authentication for user " << username << " complete." << endl;
        cout << "The clearance for " << username << " is " << clearance << endl;
        //break;
    }
};

void Login::verify_username(string username){
    string line;
    string file_username;
    string file_salt;
    string file_name = "salt.txt";
    fstream inFile(file_name);
    int count;

    if(!inFile){
        cout << "Error opening file " << file_name << endl;
        exit(3);
    }

    while(getline(inFile,line)) {
        if ((count = line.find(username,0)) != string::npos) //search for username in salt
        {
            stringstream ss(line);
            getline(ss, file_username, ':'); //reading until ':' to extract usernames from salt.txt
            ss >> file_salt;
        }
    }
    //If username was not found in salt.txt
    if(file_username != username) {
        cout << username << " was not found in " << file_name << " please run FileSystem again with -i" <<endl;
        exit(0);
    }

    //setting data to be used by verify_infomation function
    username = file_username;
    salt = file_salt;

};

bool Login::verify_hash(string hash_value, string username){
    FileSystem run;
    string line;
    string file_username;
    string file_hash;
    string file_clearance;
    string file_name = "shadow.txt";
    fstream inFile(file_name);

    if(!inFile){
        cout << "Error opening file " << file_name << endl;
        exit(3);
    }

    //Spliting data in shadow.txt by ':' and pushing it into vector
    vector<string> data;
    while(getline(inFile,line)){
        stringstream ss(line);
        string value;
        string value1;
        string value2;

        getline(ss, value,  ':'); //username
        getline(ss, value1, ':'); //hash
        ss >> value2; //clearance

        data.push_back(value);
        data.push_back(value1);
        data.push_back(value2);
    }

    for(int i=0; i < data.size(); i++ ){
        if(data[i] == username){
            file_username = data[i];
            file_hash = data[i+1];
            file_clearance = data[i+2];
        }
    }
    /*//Test code to verify that correct data is being used
     cout << endl;
     cout << "name   : " <<file_username << endl;
     cout << "hash   : " <<file_hash << endl;
     cout << "clear  : " <<stoi(file_clearance) << endl;
    */

    clearance = stoi(file_clearance);

    if(file_hash == hash_value){
        return true;
    }
    if(file_hash != hash_value){
        cerr << "ERROR" << endl;
        cerr << "Hash value: " << hash_value << " does not match "
             << file_hash << " found in " << file_name << endl;
        return false;
    }
};

int Login::get_clearance(){
    return clearance;
};
