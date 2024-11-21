CC = g++-14 $(CFLAGS)
CFLAGS = -g -O0 -std=c++14

StackCalc: StackCalc.o RealStack.o
	$(CC) -o app StackCalc.o RealStack.o -lm

StackCalc.o: StackCalc.cpp RealStack.h
	$(CC) -c StackCalc.cpp

RealStack.o: RealStack.cpp RealStack.h
	$(CC) -c RealStack.cpp

clear:
	rm -f app *.o
