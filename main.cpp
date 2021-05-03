#include "Sdisk.h"
int main()
{
    Sdisk("mydisk", 10, 8);
    cout << Sdisk.getblock(1);
    
};