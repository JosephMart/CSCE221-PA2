# a simple makefile for compiling C++ files

CC= g++ -std=c++11
LIST=abc

all: sort

sort: bubble-sort.o insertion-sort.o selection-sort.o shell-sort.o \
option.o sort.o radix-sort.o
	$(CC) -o sort bubble-sort.o insertion-sort.o selection-sort.o \
	       shell-sort.o option.o sort.o radix-sort.o

option.o: option.h option.cpp
	$(CC) -c option.cpp

bubble-sort.o: sort.h bubble-sort.cpp
	$(CC) -c bubble-sort.cpp

insertion-sort.o: sort.h insertion-sort.cpp
	$(CC) -c insertion-sort.cpp

selection-sort.o: sort.h selection-sort.cpp
	$(CC) -c selection-sort.cpp

shell-sort.o: sort.h shell-sort.cpp
	$(CC) -c shell-sort.cpp

radix-sort.o: sort.h radix-sort.cpp
	$(CC) -c radix-sort.cpp

sort.o: sort.h option.h sort.cpp
	$(CC) -c sort.cpp

clean:
	/bin/rm -f *.o sort


test:
	for egfile in 1,2,3; do            \
		echo "Installing $$egfile";     \
    done


# the directory 221-A2-code must exist
tar:
	@ /bin/rm -f *.o
	@ if [ ! -d ../CSCE221-PA2 ]; then \
	echo "Error: the directory 221-A2-code does not exist"; \
	exit 1; \
	else \
	cd ..; tar cvf 221-A2-code-submit.tar CSCE221-PA2; \
	fi
