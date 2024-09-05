CC = g++ $(CFLAGS)
CFLAGS = -g -O0

minCircleTst: minCircleTst.cpp minCircle.h R2Graph.h minCircle.o R2Graph.o
	$(CC) -o minCircleTst minCircleTst.cpp minCircle.o R2Graph.o

minCircle.o: minCircle.cpp minCircle.h R2Graph.h
	$(CC) -c minCircle.cpp

R2Graph.o: R2Graph.cpp R2Graph.h
	$(CC) -c R2Graph.cpp

clean:
	rm -f *.o minCircleTst