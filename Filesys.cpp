#include <sstream>
#include <iostream>
#include "Filesys.h"
#include "block.h"
#include<string>

using namespace std;

Filesys::Filesys(string diskname, int numberofblocks, int blocksize)
    : Sdisk(diskname, numberofblocks, blocksize)
{
    string buffer;
    getblock(0, buffer);
    /*int code = getblock(0, buffer);
    if(code == 0)
    {
        cout << "bad device";
        return;
    }*/
    rootsize = getblocksize()/10;
    fatsize = (getnumberofblocks()*5)/ getblocksize() + 1;
    //code = getblock(1, buffer);
    if (buffer[0] == '#')
    {// no filesystem
        buildfs();
    }
    else
    {
        readfs();
    }
    fssynch();
    
};

void Filesys::buildfs()
{
    //ostringstream ostream;
    for( int i = 0; i < rootsize; i++)
    {
        filename.push_back("xxxx");
        firstblock.push_back(0);
        //ostream << "xxxx" << " " << 0 << " ";
    }
    //string buffer = ostream.str();
    //vector<string> blocks = block(buffer, getblocksize());
    //putblock(1, blocks[0]);

    //ostringstream ostream2;
    fat.push_back(fatsize + 2);
    fat.push_back(1);
    for(int i = 0; i < fatsize; i++)
    {
        fat.push_back(1);
    }
    for(int i = fatsize + 2; i < getnumberofblocks(); i++)
    {
        fat.push_back(i + 1);
    }
    fat[fat.size()-1] = 0;
    /*for(int i = 0; i < fat.size(); i++)
    {
        ostream2 << fat[i] << " ";
    }
    string buffer2 = ostream2.str();
    vector<string> blocks2 = block(buffer2, getblocksize());
    for(int i =0; i< blocks2.size(); i++)
    {
        putblock(2+i, blocks2[i]);
    }*/
    fssynch();
}

int Filesys::fsclose(){
    return 0;
};

void Filesys::fssynch(){
    // write root and fat to disk
    ostringstream ostream;
    for(int i = 0; i < rootsize; i++)
    {
        ostream << filename[i] << " " << firstblock[i] << " ";
    }
    string buffer = ostream.str();
    vector<string> blocks = block(buffer, getblocksize());
    putblock(1,blocks[0]);

    ostringstream ostream2;
    for(int i = 0; i < fat.size(); i++)
    {
        ostream2 << fat[i] << " ";
    }
    string buffer2 = ostream2.str();
    vector<string> blocks2 = block(buffer2, getblocksize());

    for(int i = 0; i < blocks2.size(); i++)
    {
        putblock(2+i, blocks2[i]);
    }
};

void Filesys::readfs(){
    
    istringstream istream;
    string buffer; 
    getblock(1, buffer);
    istream.str(buffer);
    for(int i = 0; i < rootsize; i++)
    {
        string s;
        int t;
        istream >> s;
        istream >> t;
        filename.push_back(s);
        firstblock.push_back(t);
    }

    string buffer2; // will hold entire FAT
    istringstream istream2;
    for(int i = 0; i < fatsize; i++)
    {
        string b;
        getblock(i+2, b);
        buffer2 += b;
    }
    istream2.str(buffer2);
    for(int i = 0; i < getnumberofblocks(); i++)
    {
        int t;
        istream2 >> t;
        fat.push_back(t);

    }

};

int Filesys::newfile(string file){
    for(int i = 0; i < filename.size(); i++)
    {
        if (filename[i] == file)
        {
            cout << "File exists\n";
            return 0;
        }
    }
    
    for(int i = 0; i < filename.size(); i++)
    {
        if(filename[i] == "xxxx");
            {
                filename[i] = file;
                firstblock[i] = 0;
                fssynch();
                return 1;
            }
    }
    cout << "No room in root\n";
    return 0;
};

int Filesys::rmfile(string file){
    // can only remvoe empty file
    getfirstblock(file);
    return 0;
};

int Filesys::getfirstblock(string file){
    // returns first block of file returns 0 if file is empty returns -1 if file deosnt exist
    for (int i = 0; i < filename.size(); i++)
    {
        if(filename[i] == file)
        {
            return firstblock[i];
        }
    }
    cout << "no such file\n";
    return -1;
};

int Filesys::addblock(string file, string block){
    if(block.length() != getblocksize())
    {
        cout << "incorrect blocksize error\n";
        return 0;
    }
    // check if file exists first block
    // allocate block
    int first = getfirstblock(file);
    if(first == -1)
    {
        cout << " no such file\n";
        return 0;
    }
    int allocate = fat[0];
    fat[0] = fat[fat[0]]; // updates free list
    fat[allocate] = 0; // allocates in the FAT
    if(first == 0)
    {
        for(int i = 0; i < filename.size(); i++)
        {
            if(filename[i] == file)
            {
                firstblock[i] = allocate;
            }
        }
    }
    else
    {
        int b = first;
        while(fat[b] != 0)
        {
            b = fat[b];
        }
        fat[b] = allocate;
    }
    fssynch();
    putblock(allocate, block);
    return allocate;
};

int Filesys::delblock(string file, int blocknumber)
{
    if(!checkblock(file, blocknumber))
    {
        return 0;
    }
    int b = getfirstblock(file);
    if(blocknumber == b) // block we are deleating is first block
    {
        for(int i = 0; i < file[i]; i++)
        {
            if(filename[i] == file) //found it
            {
                firstblock[i] = fat[blocknumber];
                break;
            }
        }
    }
    else // block belongs to file
    {
        while(fat[b] != blocknumber)
        {
            b = fat[b];
        }
        fat[b] = fat[blocknumber];
    }

    fat[blocknumber] = fat[0]; // update free list
    fat[0] = blocknumber;
    fssynch();
    return 0;

};

int Filesys::readblock(string file, int blocknumber, string& buffer)
{
    if(checkblock(file, blocknumber))
    {
        getblock(blocknumber, buffer);
        return 1; // Successful
    }
    else
    {
        return 0; // Fail
    }
};

int Filesys::writeblock(string file, int blocknumber, string buffer){
    if (checkblock(file, blocknumber))
    {
        putblock(blocknumber, buffer);
        return 1;
    }
    else
    {
        return 0;
    }
};

int Filesys::nextblock(string file, int blocknumber){
    string buffer;
    if(checkblock(file, blocknumber))
    {
        return (fat[blocknumber]); // Successful
    }
    else
    {
        return 0; // Fail
    }
};

bool Filesys::checkblock(string file, int blocknumber){
    int b = getfirstblock(file);
    if (b == -1)
    {
        return false;
    }
    if(b == blocknumber)
    {
        return true; // handles case where first block matches block number we are looking for
    }
    while(fat[b] != 0)
    {
        if(fat[b] == blocknumber)
        {
            return true;
        }
        b = fat[b];
    }
    return false;
};

vector<string> Filesys::ls()
{
    vector<string> flist;
    for(int i = 0; i < filename.size(); i++)
    {
        if(filename[i] != "xxxxx")
        {
            flist.push_back(filename[i]);
        }
    }
    return flist;
}
