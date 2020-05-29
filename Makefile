all: main

main.o: main.c hmalloc.h
	gcc -c main.c

hmalloc.o: hmalloc.c hmalloc.h
	gcc -c hmalloc.c

main: main.o hmalloc.o
	gcc main.o hmalloc.o -o main

clean:
	rm *.o main