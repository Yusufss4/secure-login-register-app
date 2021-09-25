CFLAGS = -O3 -Wall -Wextra -Wpedantic
CC = gcc

Main: main.o sha-256.o validation.o hash-ops.o login-register.o
	$(CC) main.o sha-256.o validation.o hash-ops.o login-register.o -o Main.out

SHATest: test.o sha-256.o
	$(CC) test.o sha-256.o -o SHATest.out

test.o: test.c
	$(CC) -c test.c

main.o: main.c
	$(CC) -c main.c

validation.o: validation.c
	$(CC) -c validation.c

login-register.o: login-register.c
	$(CC) -c login-register.c

hash-ops.o: hash-ops.c
	$(CC) -c hash-ops.c

sha-256.o: sha-256.c
	$(CC) -c sha-256.c

.PHONY: clean
clean:
	rm -rf *.o
