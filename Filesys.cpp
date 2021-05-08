#include <sstream>
#include <iostream>

using namespace std;

Filesys::Filesys(string diskname, int numberofblocks, int blocksize){
    diskname(diskname), numberofblocks(numberofblocks), blocksize(blocksize);
    /*string buffer;
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
    }*/
    // Changed during Lecture 8
    rootsize = getblocksize()/10;
    fatsize = (getnumberofblocks()*5)/ blocksize + 1;
    
};

void Filesys::buildfs()
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

void fssynch(){
    // wrtie root and fat to disk
    ostringstream ostream;
    for(int i = 0; i < rootsize; i++)
    {
        ostream << filename[i] << " " << firstblock[i] << " ";
    }
    string buffer = ostream.str();
    vector<string> blocks = block(buffer, getblocksize());
    putblock(1,blocks[0])

    ostringstream ostream2;
    for(i = 0; i < fat.size(); i++)
    {
        ostream2 << fat[i] << " ";
    }
    string buffer2 = ostream2.str();
    vector<string> blocks2 = block(buffer2, getblocksize);

    for(i = 0; i < blocks2[i]; i++)
    {
        putblock(2+i, blocks2[i])
    }
};

void Filesys::readfs(){
    
    istringstream istream;
    string buffer; 
    getblock(1, buffer);
    istream.str(buffer);
    for(i = 0; i < rootsize; i++)
    {
        string s, int t;
        istream >> s;
        istream >> t;
        filename.push_back(s);
        firstblock.push_back(t);
    }

    string buffer // will hold entire FAT
    istringstream istream2;
    for(int i = 0; i < fatsize; i++)
    {
        string b;
        getblock(i+2, b);
        buffer += b;
    }
    istream2.str(buffer);
    for(int i = 0; i < getnumberofblocks(); i++)
    {
        int t;
        istream2 >> t;
        fat.pushback(t);

    }

};

int Filesys::newfile(string file){
    for(int i = 0; i < filename.size(); i++)
    {
        if (filename[i] == file)
        {
            cout << "File exists";
        }
        return 0;
    }
    
    for(int i = 0; i < filename.size(); i++)
    {
        if filename[i] == "xxxx";
            {
                filename[i] = file;
                firstblock[i] = 0;
                fssynch();
                return 1;
            }
    }
    cout << "No room in root"
    return 0;
};

int rmfile(string file){

};

int Filesys::getfirstblock(string file){
    // returns first block of file returns 0 if file is empty returns -1 if file deosnt exist
    
};

int Fielsys::addblock(string file, string block){

};

int delblock(string file, int blocknumber){

};

int readblock(string file, int blocknumber, string& buffer){

};

int writeblock(string file, int blocknumber, string buffer){

};

int nextblock(string file, int blocknumber){

};