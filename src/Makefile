IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -ggdb -O3 -Wall -Wextra -Wpedantic

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = hash-ops.h login-register.h sha-256.h validation.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o hash-ops.o login-register.o sha-256.o validation.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
