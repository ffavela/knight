CC = gcc
CFLAGS = -c -O2

all: knight

knight: knight.o move.o
	$(CC) -o knight knight.o move.o

knight.o: knight.c headers.h
	$(CC) $(CFLAGS) knight.c

move.o: move.c headers.h
	$(CC) $(CFLAGS) move.c

clean:
	rm -rf *o knight
