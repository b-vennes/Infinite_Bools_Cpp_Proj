all: test

test: main.o infiniteBools.o
	g++ -o test main.o infiniteBools.o

infiniteBools.o: infiniteBools.cpp infiniteBools.h
	g++ -c infiniteBools.cpp

main.o: main.cpp infiniteBools.h
	g++ -c main.cpp

clean:
	/bin/rm -rf test *.o
