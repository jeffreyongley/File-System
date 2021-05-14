#include "Table.h"
#include <vector>
#include "block.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

Table::Table(string diskname, int blocksize, int numberofblocks, string flatfile, string indexfile)
    : Filesys(diskname, numberofblocks, blocksize)
{
    this->flatfile = flatfile;
    this->indexfile = indexfile;
    numrec = 0;
    newfile(flatfile);
    newfile(indexfile);
};
int Table::Build_Table(string input_file)
{
    ostringstream indexstream, flatstream;
    ifstream infile;
    infile.open(input_file);
    if (infile.bad())
    {
        return 0;
    }
    string s;
    getline(infile, s);
    while(infile.good())
    {
        string key = s.substr(0, 5);
        vector <string> blocks = block(s, getblocksize());
        int b = addblock(flatfile, blocks[0]);
        indexstream << key << " " << b << " ";
        numrec++;
        getline(infile, s);
    }
    string buffer = indexstream.str();
    vector<string> blocks = block(buffer, getblocksize());
    for (int i = 0; i < blocks.size(); i++)
    {
        int b = addblock(indexfile, blocks[i]);
    }
    return 1;
};
int Table::Search(string key)
{
    int b = IndexSearch(key);
    if (b <= 0)
    {
        return -1;
    };
    string buffer;
    b = readblock(flatfile, b, buffer);
    cout << buffer;
    return b;
};
int Table::IndexSearch(string key)
{
    istringstream instream;
    string bigbuffer;

    int b = getfirstblock(indexfile);
    if(b <= 0)
    {
        return 0;
    };
    while(b != 0)
    {
        string buffer;
        int error = readblock(indexfile, b, buffer);
        bigbuffer += buffer;
        b = nextblock(indexfile,b);
    };
    //index file is a string in big buffer
    // process big buffer
    instream.str(bigbuffer);
    for(int i = 0; i < numrec; i++)
    {
        string value;
        int block;
        instream >> value >> block;
        if(value == key)
        {
            return block;
        }
    };
    return -1;
    // end index search
};
