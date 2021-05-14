#ifndef TABLE_H
#define TABLE_H
#include <string>
#include "Filesys.h"


class Table: public Filesys
{
    public:

    Table(string diskname, int blocksize, int numberofblocks, string flatfile, string indexfile);
    int Build_Table(string input_file);
    int Search(string key);
    private:

    string flatfile;
    string indexfile;
    int numrec; // number of records
    int IndexSearch(string key);
};
#endif