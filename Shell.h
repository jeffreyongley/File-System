
#include "Filesys.cpp"

class Shell: public Filesys
{
    Public:
    Shell(string filename, int blocksize, int numberofblocks);
    int dir(); // lists all files
    int add(string file); // add a new file using input from the keyboard
    int del(string file); //deletes the file
    int type(string file);// lists the contents of the file
    int copy(string file1, string file2); // copies file1 to file2
};