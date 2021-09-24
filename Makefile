CFLAGS = -O3 -Wall -Wextra -Wpedantic
CC = gcc

Main: main.o sha-256.o
	$(CC) main.o sha-256.o -o Main.out

SHATest: test.o sha-256.o
	$(CC) test.o sha-256.o -o SHATest.out

test.o: test.c
	$(CC) -c test.c

main.o: main.c
	$(CC) -c main.c
sha-256.o: sha-256.c
	$(CC) -c sha-256.c

.PHONY: clean
clean:
	rm -rf *.o
