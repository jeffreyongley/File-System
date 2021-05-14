Project: Sdisk.o Filesys.o block.o Table.o Shell.o Test_Shell.o
	c++ -g Sdisk.o Test_Shell.o Filesys.o block.o Shell.o Table.o -o Project
block.o: block.cpp
	c++ -c -g block.cpp
Sdisk.o: Sdisk.cpp
	c++ -c -g Sdisk.cpp
Filesys.o: Filesys.cpp
	c++ -c -g Filesys.cpp
Table.o: Table.cpp
	c++ -c -g Table.cpp
Shell.o: Shell.cpp
	c++ -c -g Shell.cpp
Test_Shell.o: Test_Shell.cpp
	c++ -c -g Test_Shell.cpp
clean:
	rm *.o rm Project
