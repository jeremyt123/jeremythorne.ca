CC=gcc
CFLAGS=-Wall -g -std=c99
LDFLAGS=-lm

fleschIndex: fleschIndex.o
	$(CC) $(LDFLAGS) fleschIndex.o -o fleschIndex

fleschIndex.o: fleschIndex.c
	$(CC) $(CFLAGS) -c fleschIndex.c

memtest: fleschIndex
	valgrind ./fleschIndex

clean:
	rm fleschIndex fleschIndex.o
