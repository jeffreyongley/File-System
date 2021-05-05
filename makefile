Project2: Sdisk.o main.o
	c++ -o Project2 Sdisk.o main.o
Sdisk.o:Sdisk.cpp
	c++ -c Sdisk.cpp
main.o: main.cpp
	c++ -c main.cpp
clean:
	rm *.o
