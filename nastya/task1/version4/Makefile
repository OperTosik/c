CC=g++
CFLAGS=-fno-elide-constructors -std=c++11

all: a.out

a.out: main.o  task.o
	$(CC) $(CFLAGS) main.o task.o

main.o: main.cpp head.h test1.cpp test2.cpp
	$(CC) -c $(CFLAGS) main.cpp

task.o: task.cpp head.h
	$(CC) -c $(CFLAGS) task.cpp

clean:
	rm *.o a.out