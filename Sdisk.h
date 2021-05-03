//#ifndef SDISK_H
//#define SDISK_H

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

class Sdisk
{
    public:
    Sdisk(string diskname, int numberofblocks, int blocksize)
    {
        ofstream file (diskname);
        for (int i = 0; i < numberofblocks * blocksize; i++)
        {
            file << "#";
        }

        file.close();
    };
    int getnumberofblocks()
    {
        return numberofblocks;
    };
    int getblocksize()
    {
        return blocksize;
    };
    int getblock(int blocknumber, string buffer)
    {
        fstream f;
        f.open(diskname.c_str(), ios::in | ios::out);

        f.seekg(blocknumber * blocksize);
        char c;
        for (int i = 0; i < blocksize; i++)
        {
            f.get(c);
            buffer.push_back(c);
        }
        return 0;

    };
    int putblock(int blocknumber, string buffer)
    {
        fstream f;
        f.open(diskname.c_str(), ios::in | ios::out);

        f.seekg(blocknumber * blocksize);
        char c;
        for (int i = 0; i < blocksize; i++)
        {
            f.put(buffer[i]);
        }
        return 0;
    };

    private:
    string diskname;
    int numberofblocks;
    int blocksize;
    string buffer;
};
//#endif
