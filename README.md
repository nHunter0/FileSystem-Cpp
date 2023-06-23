# File System in C++

This repository contains a C++ implementation of a simulated file system that utilizes the MD5 hashing algorithm for secure user authentication.

## Getting Started

These instructions will help you get a copy of the project and run it on your local machine for development and testing purposes.

### Prerequisites

To compile and run this code, you will need the `gcc` compiler installed on your machine.

### Files required

All the files required to build and run the program are listed below. They all should be in the same directory, including two blank files named `salt.txt` and `shadow.txt`.

- FileSystem.cpp
- FileSystem.h
- Initialize.cpp
- Initialize.h
- Login.cpp
- Login.h
- main.cpp
- md5.cpp
- md5.h
- System.cpp
- System.h
- salt.txt
- shadow.txt

### Building the program

To build the program, navigate to the directory containing the source files and run the following command:

```
$ g++ FileSystem.cpp FileSystem.h Initialize.cpp Initialize.h Login.cpp Login.h main.cpp md5.cpp md5.h System.cpp System.h -o FileSystem
```

Alternatively, you can use the following command:

```
$ g++ *.cpp -o FileSystem
```

### Running the program

Once the program is built, run the FileSystem with argument `-i` to initialize the user.

```
$ ./FileSystem -i
```

After the user creation process ends, run FileSystem again without any arguments.

```
$ ./FileSystem
```

## Program Description

The initial run of the program with the `-i` flag will prompt for a new username and password, as well as a user clearance level. If the given username does not already exist in `salt.txt` and `shadow.txt`, the program will generate a salt value, hash the password with the salt, and store this information along with the username and clearance level.

After a user is successfully created, running `./FileSystem` without arguments will allow the user to log in. The user will be presented with several options to interact with the "file system", such as create, append, read, write, list, save, or exit. Each action is subject to clearance levels and rules defined by the Bell–LaPadula model.

## References

The implementation of the MD5 hashing function used in this project is taken from: [http://www.zedwood.com/article/cpp-md5-function](http://www.zedwood.com/article/cpp-md5-function) written by Frank Thilo.

## Disclaimer

This program is for educational purposes only and is not intended for use in a production environment. It does not provide robust security and should not be used for storing sensitive information.
