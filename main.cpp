//main.cpp
#include <iostream>

#include "FileSystem.h"
#include "System.h"
#include "md5.h"
#include "time.h"

using namespace std;


int main(int argc, char *argv[])
{
    srand(time(NULL));
    FileSystem run;
    System system;


    cout << "MD5 test : " << md5("This is a test") << endl;
    //expected output = ce114e4501d2f4e2dcea3e17b546f339

    if(argc > 1){
        if (string(argv[1]) == "-i"){ //If -i is present
            run.initialize();
        }

        else { //If arg is present and -i is not present
            cout << "Argument is not recognized as a command" << endl;
        }
    }
    else { //Run without -i
        system.load_file("Files.store");
        run.login();
    }

    return 0;
};


