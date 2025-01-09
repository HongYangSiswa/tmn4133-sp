# TMN4113 System Programming Project 

### 📑 Table of Contents

- [Project Requirements](#-project-requirements)
- [Compile C program](#-compile-c-program)
- [Run Program](#-run-program)
- [Usage of keylogger](#️-usage-of-keylogger)
- [Test Case for Task B](#-test-case-for-task-b)
- [Manual](#-manual)

### 🧑‍💻 Group Member

1. 79880 Lim Hong Yang
2. 78000 Gerrard Keneth Sahol
3. 78483 Peter Ligan Anak Mamat
4. 79065 Chin Teck Yung

### ✔️ Project Requirements

Ubuntu VM

```sh
Ubuntu 24.04.1 LTS
```
[Download Ubuntu Image](https://ubuntu.com/download/desktop)

Update system
```sh
sudo apt update -y && sudo apt upgrade -y
```

Install GCC
```sh
sudo apt install gcc 
```


### ⚙️ Compile C program

```sh
gcc ./taskA/supercommand.c -o ./taskA/supercommand

gcc ./taskB/supercommand.c -o ./taskB/supercommand
```

### 🏃‍♂️‍➡️ Run Program

Menu System

```
./supercommand
```

Commandline Arguments (See user manual [below](#commandline-args-manual))
```
./supercommand -m 1 1 hi.txt #create a file
```

### 🔬 Test Case for Task B

**[FILE] operation:**
```
1   Create or open a file
./supercommand -m 1 1 ./test/test.txt

2   Change file permissions
./supercommand -m 1 2 ./test/test.txt 

3   Read from a file
./supercommand -m 1 3 ./test/test.txt 

4   Write to a file
./supercommand -m 1 4 ./test/test.txt 

5   Delete a file
./supercommand -m 1 5 ./test/test.txt
```


**[DIRECTORY] operation:**
```
1   Create a directory
./supercommand -m 2 1 ./test2

2   Remove a directory
./supercommand -m 2 1 ./test2

3   Print the current working directory
./supercommand -m 2 1

4   List the contents of a directory
./supercommand -m 2 1 .
```


**[KEYLOGGER] operation:**
```
sudo ./supercommand -m 3 keylog.txt
```


### 📃 Manual
```
SUPERCOMMAND(1)                User Commands               SUPERCOMMAND(1)

NAME
       supercommand - A tool for file operations, directory management, and keylogging

SYNOPSIS
       supercommand [-m mode] [operation_code] [file_or_directory]
       supercommand [-h|--help]

DESCRIPTION
       supercommand is a command-line utility that allows users to perform various system tasks such as
       file operations, directory management, and keylogging. It is designed to be simple to use and flexible
       with a range of modes to interact with the system. Some operations require root privileges.

OPTIONS
       -m mode
           Specifies the operation mode. The available modes are:
           1   File operations
           2   Directory operations
           3   Keylogger

       -h, --help
           Displays the help manual with information about the usage, available options, modes, and examples.

       operation_code
           The operation to be performed, dependent on the selected mode. See below for available codes.

       file_or_directory
           The file or directory involved in the operation (e.g., filename for file operations, directory name for
           directory operations).

FILE OPERATIONS (MODE 1)
       -m 1 <operation_code> <filename>
           The following operations are available in file operation mode:
           1   Create or open a file
           2   Change file permissions
           3   Read from a file
           4   Write to a file
           5   Delete a file

           Example usage:
           Create/Open a file:
               supercommand -m 1 1 testfile.txt
           Change file permissions:
               supercommand -m 1 2 testfile.txt
           Read from a file:
               supercommand -m 1 3 testfile.txt
           Write to a file:
               supercommand -m 1 4 testfile.txt
           Delete a file:
               supercommand -m 1 5 testfile.txt

DIRECTORY OPERATIONS (MODE 2)
       -m 2 <operation_code> <directory_name>
           The following operations are available in directory operation mode:
           1   Create a directory
           2   Remove a directory
           3   Print the current working directory
           4   List the contents of a directory

           Example usage:
           Create a new directory:
               supercommand -m 2 1 testdir
           Remove a directory:
               supercommand -m 2 2 testdir
           Print the current directory:
               supercommand -m 2 3 .
           List contents of a directory:
               supercommand -m 2 4 .

KEYLOGGER (MODE 3)
       -m 3 <log_filename>
           This mode enables keystroke logging and saves the recorded keystrokes into the specified log file.
           Example usage:
           Start keylogging and save to a log file:
               sudo supercommand -m 3 keylog.txt

EXITING THE PROGRAM
       To exit the program, use the following command:
           exit
       Alternatively, terminate the program with `Ctrl+C`.

USAGE EXAMPLES
       1. Create a file named "testfile.txt":
            supercommand -m 1 1 testfile.txt
       2. Change file permissions for "testfile.txt":
            supercommand -m 1 2 testfile.txt
       3. List contents of the current directory:
            supercommand -m 2 4 .
       4. Start logging keystrokes to "keylog.txt":
            supercommand -m 3 keylog.txt

ERRORS
       Permission denied
           This error occurs when attempting to perform an operation that requires root privileges. Use `sudo` to
           execute with root access:
               sudo supercommand -m <mode> <operation_code> <file_or_directory>

       Operation not permitted
           This error may occur if the file or directory does not exist or is inaccessible. Ensure that the file
           or directory is valid and that you have permission to perform the requested operation.

```

