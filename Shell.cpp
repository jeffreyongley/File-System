 #include "Shell.h"
 #include "block.h"

 int Shell::add(string file, string buffer)
 {
     int error = newfile(file);
     if (error < 1)
     {
         cout << "sorry";
         return 0;
     }
     vector<string> blocks = block(buffer, getblocksize());
     for (int i = 0; i < blocks.size(); i++)
     {
         addblock(file, blocks[i]);
     }
     return 1;
 };
// read file into string buffer
int Shell:: copy(string file1, string file2)
{
    // create file2
    string buffer;
    int block = getfirstblock(file1);
    if (block < 0)
    {
        cout << "no such file";
        return 0;
    }
    if(block == 0)
    {
        cout << "empty file";
        return 1;
    }
    while(block != 0)
    {
        string b;
        readblock(file1, block, b);
        addblock(file2, b);
        buffer += b;
        block = nextblock(file1, block);
    }
    return 0;
};

int Shell:: del(string file)
{
    while(getfirstblock(file))
    {
        delblock(file, getfirstblock(file));
    }
    rmfile(file);
    return 0;
};

int Shell::dir()
{
    vector<string> flist=ls();
    for(int i = 0; i <flist.size(); i ++)
    {
        cout << flist[i] << endl;
    }
    return 0;
};