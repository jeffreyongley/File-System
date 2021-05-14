#ifndef SHELL_H
#define SHELL_H
#include "Filesys.h"


class Shell: public Filesys
{
    public:
    Shell(string filename, int blocksize, int numberofblocks);
    int dir(); // lists all files
    int add(string file, string buffer); // add a new file using input from the kSeyboard
    int del(string file); //deletes the file
    int type(string file);// lists the contents of the file
    int copy(string file1, string file2); // copies file1 to file2
};
#endif