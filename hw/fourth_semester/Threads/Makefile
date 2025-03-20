CC = g++ $(CFLAGS)
CFLAGS = -g -O0

all: threadtst semExample parallelIntegral parallelMatrixSTL

threadtst: threadtst.cpp
	$(CC) -o threadtst threadtst.cpp -lpthread

semExample: semExample.cpp
	$(CC) -o semExample semExample.cpp -lpthread

parallelIntegral: parallelIntegral.cpp
	$(CC) -o parallelIntegral parallelIntegral.cpp -lpthread

parallelMatrixSTL: parallelMatrixSTL.cpp
	$(CC) -o parallelMatrixSTL parallelMatrixSTL.cpp -lpthread

clean:
	rm -f threadtst semExample parallelIntegral parallelMatrixSTL *.o a.out core leak.out
