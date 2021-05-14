This Project was created as a course Project for CSE 4610 Operating Systems II. It was completed over the course of a 16 week semester in the spring of 2021.

File Descriptions

Sdisk.h/Sdisk.cpp
These declare and define a class Sdisk that creates a virtual disk for our system. The disk is a text file filled with "#" to represent empty space.

Filesys.h/Filesys.cpp
These declare the Filesys class which inherits the Sdisk class. This utilizes the created Sdisk and writes to it and reads from it.

Shell.h/ Shell.cpp
this creates the shell prompt for our file system and allows us to use linux style text commands to create copy and delete folders.

Table.h/ Table.cpp
These give our program the ability to read in an example data table and store its data to the disk.

Block.h 
This is a provied block program to seperate any data into blocks of a set size. It is used throughout the program to block the data for reading and writing purposes.

Test_Sdisk.cpp/ Test_Filesys.cpp/ Test_Shell.cpp 
These files are used to test each part of the project induvidually.
