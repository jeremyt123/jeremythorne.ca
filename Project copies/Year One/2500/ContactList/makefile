CC = gcc
CFLAGS = -ansi -Wall -I$(INCLUDEDIR)

INCLUDEDIR = ./includes/
SRCDIR = ./src/
BINDIR = ./bin/

all: $(BINDIR)contactList

$(BINDIR)contactList: $(BINDIR)main.o $(BINDIR)func.o
	$(CC) $(BINDIR)main.o $(BINDIR)func.o -o $@

$(BINDIR)main.o: $(SRCDIR)main.c
	$(CC) $(CFLAGS) -c $(SRCDIR)main.c -o $@

$(BINDIR)func.o: $(SRCDIR)func.c
	$(CC) $(CFLAGS) -c $(SRCDIR)func.c -o $@

clean:
	rm ./bin/*.o ./bin/contactList ./myContactList.db

memtest: $(BINDIR)contactList
	valgrind ./bin/contactList