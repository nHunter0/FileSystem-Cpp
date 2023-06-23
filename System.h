#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED
#include <vector>
#include <string>
class System{
private:
    int clearance;
    std::string username;
    std::string userinput;
    //Master arrays
    std::vector<std::string> files;
    std::vector<std::string> owners;
    std::vector<std::string> clearances;
    //Temp arrays to be cleared
    std::vector<std::string> new_files;
    std::vector<std::string> new_owners;
    std::vector<std::string> new_clearances;
public:
    void load_file(std::string);
    std::string user_input();
    void display_menu();
    void run_menu(std::string);
    void rerun_menu();
    void set_data(std::string,int);
    bool verify_file(std::string);
    bool verify_read(std::string);
    bool verify_write(std::string);
    bool verify_append(std::string);
    void write_file(std::string,std::string,std::string);
    //Menu options:
    void create();
    void append();
    void read();
    void write();
    void list();
    void save();
    void exit_system();

};


#endif // SYSTEM_H_INCLUDED
