CC=g++
CFLAGS=-fno-elide-constructors -std=c++11 -g

all: a.out

a.out: main.o  task.o test1.o test2.o
	$(CC) $(CFLAGS) main.o task.o test1.o test2.o

main.o: main.cpp head.h
	$(CC) -c $(CFLAGS) main.cpp

task.o: task.cpp head.h
	$(CC) -c $(CFLAGS) task.cpp

test1.o: test1.cpp test.h
	$(CC) -c $(CFLAGS) test1.cpp

test2.o: test2.cpp test.h
	$(CC) -c $(CFLAGS) test2.cpp

clear:
	rm *.o a.out