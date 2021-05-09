Project: Sdisk.o Filesys.o main.o block.o
	c++ Sdisk.o main.o Filesys.o block.o -o Project
block.o: block.cpp
	c++ -c block.cpp
Sdisk.o: Sdisk.cpp
	c++ -c Sdisk.cpp
Filesys.o: Filesys.cpp
	c++ -c Filesys.cpp
main.o: main.cpp
	c++ -c main.cpp
clean:
	rm *.o Project
