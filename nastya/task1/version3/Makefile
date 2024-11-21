a.out: main.o  task.o
	g++ main.o task.o
main.o: main.cpp head.h test1.cpp test2.cpp
	g++ -c main.cpp
task.o: task.cpp head.h
	g++ -c task.cpp