FLAGS = -Wall  -g

a.out :  tmain.o tree.o myfun.o
	g++ $(FLAGS) tmain.o tree.o myfun.o

tmain.o :  tmain.cpp tree.h
	g++ -c $(FLAGS) -o tmain.o tmain.cpp

myfun.o :  myfun.cpp tree.h
	g++ -c $(FLAGS) -o myfun.o myfun.cpp

clean :
	rm tmain.o myfun.o a.out
