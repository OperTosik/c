CC = g++-14 $(CFLAGS)
CFLAGS = -g -O0

all: draw prodCons threadtst semExample randDevice \
	parallelIntegral parallelMatrixSTL generateMatrix

draw:
	$(CC) -o draw draw.cpp -lpthread

prodCons: prodCons.cpp
	$(CC) -o prodCons prodCons.cpp -lpthread

threadtst: threadtst.cpp
	$(CC) -o threadtst threadtst.cpp -lpthread

semExample: semExample.cpp
	$(CC) -o semExample semExample.cpp -lpthread

randDevice: randDevice.cpp
	$(CC) -o randDevice randDevice.cpp

parallelIntegral: parallelIntegral.cpp
	$(CC) -o parallelIntegral parallelIntegral.cpp -lpthread

parallelMatrixSTL: parallelMatrixSTL.cpp
	$(CC) -o parallelMatrixSTL parallelMatrixSTL.cpp -lpthread

generateMatrix: generateMatrix.cpp
	$(CC) -o generateMatrix generateMatrix.cpp

clean:
	rm -f draw prodCons threadtst semExample randDevice \
		parallelIntegral parallelMatrixSTL generateMatrix \
		*.o a.out core leak.out
