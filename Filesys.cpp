#include <sstream>
#include <iostream>

using namespace std;

Filesys::Filesys(string diskname, int numberofblocks, int blocksize){
    diskname(diskname), numberofblocks(numberofblocks), blocksize(blocksize);
   // unsure if needed
    //this->diskanme = diskname;
    //this->numberofblocks = numberofblocks;
    //this->blocksize = blocksize;
    string buffer;
    int code = getblock(0, buffer);
    if(code == 0)
    {
        cout << "bad device";
        return;
    }
    rootsize = getblocksize()/10;
    fatsize = (getnumberofblocks()*5)/ getblocksize() + 1;
    int code = getblock(1, buffer);
    if (buffer[0] == "#")
    {// no filesystem
        buildfs();
    }
    else
    {
        readfs();
    }
    
};

void Filesys:: buildfs()
{
    ostringstream ostream;
    for( int i = 0; i < rootsize; i++)
    {
        filename.push_back("xxxx");
        firstblock.push_back(0);
        ostream << "xxxx" << " " << 0 << " ";
    }
    string buffer = ostream.str();
    vector<string> blocks = block(buffer, getblocksize());
    putblock(1, blocks[0]);

    ostringstream ostream2;
    fat.push_back(fatsize + 2);
    //ostream2 << fatsize + 2 << " ";
    fat.push_back(1);
    //ostream2 << 1 << " ";
    for(i = 0; i < fatsize; i++)
    {
        fat.push_back(1);
        //ostream2 << 1 << " ";
    }
    for(i = fatsize + 2; i < getnumberofblocks(); i++)
    {
        fat.push_back(i + 1);
    }
    fat[fat.size()-1] = 0;
    for(i = 0; i < fat.size()0; i++)
    {
        ostream2 << fat[i] << " ";
    }
    string buffer2 = ostream2.str();
    vector<string> blocks2 = block(buffer, getblocksize());
    for(int i =0; i< blocks2.size(); i++)
    {
        putblock(2+i, blocks2[i]);
    }
}

int fsclose(){

};

int fssynch(){

};

int newfile(string file){

};

int rmfile(string file){

};

int getfirstblock(string file){

};

int addblock(string file, string block){

};

int delblock(string file, int blocknumber){

};

int readblock(string file, int blocknumber, string& buffer){

};

int writeblock(string file, int blocknumber, string buffer){

};

int nextblock(string file, int blocknumber){

};