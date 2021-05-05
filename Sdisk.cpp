
#include "Sdisk.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
Sdisk::Sdisk(string diskname, int numberofblocks, int blocksize)
{
    this->diskname = diskname;
    this->numberofblocks = numberofblocks;
    this->blocksize = blocksize;
    ofstream file (diskname);
    for (int i = 0; i < numberofblocks * blocksize; i++)
    {
        file << "#";
    }

    file.close();
};

int Sdisk::getnumberofblocks()
{
    return numberofblocks;
};

int Sdisk::getblocksize()
{
    return blocksize;
};

int Sdisk::getblock(int blocknumber, string& buffer)
{
    fstream f;
    f.open(diskname.c_str(), ios::in | ios::out);

    f.seekg(blocknumber * getblocksize());
    for (int i = 0; i < getblocksize(); i++)
    {
        char c = f.get();
        buffer.push_back(c);
    }
    return 0;

};

int Sdisk::putblock(int blocknumber, string buffer)
{
    fstream f;
    f.open(diskname.c_str(), ios::in | ios::out);
    f.seekg(blocknumber * getblocksize());
    for (int i = 0; i < getblocksize(); i++)
    {
        char c = buffer[i];
        f.put(c);
    }
    return 0;
};
