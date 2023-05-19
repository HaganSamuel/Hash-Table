all: test3

test3: test3.o program3.o
	g++ -o test3 test3.o program3.o

test3.o: test3.cpp
	g++ -c test3.cpp

program3.o: program3.cpp
	g++ -c program3.cpp

clean:
	rm -f test3 *.o

run: test3
	./test3