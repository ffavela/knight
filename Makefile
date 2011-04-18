CC = gcc
CFLAGS = -c -O2

all: knight

knight: knight.o move.o
	$(CC) -o knight knight.o move.o

knight.o: knight.c
	$(CC) $(CFLAGS) knight.c

move.o: move.c
	$(CC) $(CFLAGS) move.c

clean:
	rm -rf *o knight
