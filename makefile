Project: Sdisk.o Filesys.o main.o block.o
	c++ -g Sdisk.o main.o Filesys.o block.o -o Filesys
block.o: block.cpp
	c++ -c -g block.cpp
Sdisk.o: Sdisk.cpp
	c++ -c -g Sdisk.cpp
Filesys.o: Filesys.cpp
	c++ -c -g Filesys.cpp
main.o: main.cpp
	c++ -c -g main.cpp
clean:
	rm *.o
