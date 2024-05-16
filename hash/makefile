all: main.o func.o
	main.o func.o && rm*.o && ./a.out

main.o: main.c
	gcc -c main.c

func.o: func.c
	gcc -c func.c