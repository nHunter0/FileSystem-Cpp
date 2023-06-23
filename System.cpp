//System.cpp
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ostream>
#include <iomanip>
#include <sstream>

#include "System.h"

using namespace std;

void System::load_file(string fileName){
    fstream inFile;
    string line;
    string name;
    string owner;
    string clearance;

    inFile.open(fileName);

    if(!inFile){ //File does not exist
        return;
    }

    while(getline(inFile,line)){
        stringstream ss(line);
        getline(ss,name,':');
        getline(ss,owner,':');
        getline(ss,clearance,':');

        files.push_back(name);
        owners.push_back(owner);
        clearances.push_back(clearance);
    }
    inFile.close();
};

void System::display_menu(){
    cout << "Options: (C)reate, (A)ppend, (R)ead, (W)rite, (L)ist, (S)ave or (E)xit." << endl;
};

void System::run_menu(string userinput){
    if(userinput == "C" || userinput == "c") //Create
    {
        create();
    }

    else if(userinput == "A" || userinput == "a") //Append
    {
        append();
    }

    else if(userinput == "R" || userinput == "r") //Read
    {
        read();
    }

    else if(userinput == "W" || userinput == "w") //Write
    {
        write();
    }

    else if(userinput == "L" || userinput == "l") //List
    {
        list();
    }

    else if(userinput == "S" || userinput == "s") //Save
    {
        save();
    }

    else if(userinput == "E" || userinput == "e") //Exit
    {
        exit_system();
    }

    else
    {
        cout << userinput << " is not listed, try agin." << endl;
        rerun_menu();
    }
};

void System::rerun_menu(){
    display_menu();
    userinput = user_input();
    run_menu(userinput);
};

void System::set_data(string username, int clearance){
    this->clearance = clearance;
    this->username = username;
    load_file("Files.store");
};

bool System::verify_file(string fileName){
    if (find(files.begin(), files.end(), fileName) != files.end()){
        return false;
    }
    return true;
};

bool System::verify_read(string fileName){
    int index = find(files.begin(), files.end(), fileName) - files.begin();

    if(stoi(clearances[index]) <= clearance){ //No read up
        return true;
    }
    else{
        return false;
    }
};

bool System::verify_write(string fileName){
    int index = find(files.begin(), files.end(), fileName) - files.begin();

    if(stoi(clearances[index]) >= clearance){ //No write down
        return true;
    }
    else{
        return false;
    }
};

bool System::verify_append(string fileName){
    int index = find(files.begin(), files.end(), fileName) - files.begin();

    if(stoi(clearances[index]) <= clearance){
        return true;
    }
    else{
        return false;
    }
};

void System::write_file(string file, string owner, string clearance){
    ofstream file_out("Files.store",ios::app);
    file_out << file << ':' << owner << ':' << clearance << '\n';
};

string System::user_input(){
    cin >> userinput;
    return userinput;
};

void System::create(){
    fstream inFile;
    inFile.open("Files.store");

    //Creating Files.store if file does not exist
    if( !inFile ){
        cout << "Creating Files.store... " <<endl;
        ofstream inFile("Files.store");
    }

    string fileName;
    cout << "Filename: ";
    cin >> fileName;

    if(verify_file(fileName)){
        cout << "File created." << endl;
        cout << username << ':' << fileName << ':' <<
        clearance << endl;

        files.push_back(fileName);  new_files.push_back(fileName);
        owners.push_back(username); new_owners.push_back(username);
        clearances.push_back(to_string(clearance)); new_clearances.push_back(to_string(clearance));

        rerun_menu();
    }
    else if(!verify_file(fileName)){
        cerr << "Error: File exists in FileSystem already " << endl;
        rerun_menu();
    }
    inFile.close();
};

void System::append(){
    string fileName;
    cout << "Filename: ";
    cin >> fileName;

    if(verify_file(fileName)){
        cerr << "Error: File does not exists in FileSystem " << endl;
        rerun_menu();
    }

    if(!verify_append(fileName)){
        cout << "Failure." << endl;
    }
    else{
        cout << "Success." << endl;
    }

    rerun_menu();
};

void System::read(){
    string fileName;
    cout << "Filename: ";
    cin >> fileName;

    if(verify_file(fileName)){
        cerr << "Error: File does not exists in FileSystem " << endl;
        rerun_menu();
    }


    if(!verify_read(fileName)){
        cout << "Failure, no reading up." << endl;
    }
    else{
        cout << "Success." << endl;
    }

    rerun_menu();
};

void System::write(){
    string fileName;
    cout << "Filename: ";
    cin >> fileName;

    if(verify_file(fileName)){
        cerr << "Error: File does not exists in FileSystem " << endl;
        rerun_menu();
    }

    if(!verify_write(fileName)){
        cout << "Failure, no writing down." << endl;
    }
    else{
        cout << "Success." << endl;
    }

    rerun_menu();
};

void System::list(){

    if(files.size() == 0){
        cout << "No files found in the FileSystem records" << endl;
        rerun_menu();
    }

    cout << files.size() << " files found in Files.Store..." << endl;
    cout << "Owner" << '\t' << "   File" << '\t' << "   Clearance" << endl;
    cout << string(28,'-') << endl;
    for(int i=0; i<files.size(); i++){
        cout << owners[i] << ' ' << setw(14-owners[i].size())
             << files[i] << '\t' << "   "
             << clearances[i] << endl;
    }
    rerun_menu();
};

void System::save(){
    if(new_files.size() == 0){
        cout << "Nothing new to be saved " << endl;
        rerun_menu();
    }

    for(int i=0; i<new_files.size(); i++){
        write_file(new_files[i], new_owners[i], new_clearances[i]);
       //cout << new_owners[i] << ':' << new_files[i] << ':' << new_clearances[i] << '\n'; //Files that are being saved
    }

    //clearing arrays so that save function does not resave same items
    new_files.clear();
    new_owners.clear();
    new_clearances.clear();

    cout << "Saved successfully" << endl;
    rerun_menu();
};

void System::exit_system(){
    string option;
    //string user_input;
    cout << "Shut down the FileSystem? (Y)es or (N)o" << endl;
    cin >> option;

    if(option == "Y" || option == "y" || option == "Yes" || option == "yes"){
        exit(0);
    }

    else if((option == "N" || option == "n" || option == "No" || option == "no")) {
        rerun_menu();
    }
};
