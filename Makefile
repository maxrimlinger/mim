CC=gcc
CFLAGS=-I -Wall -Wextra -pedantic -g

LIBS=-lncurses

DEPS = $(wildcard *.h)

OBJ = $(patsubst %.c, %.o, $(wildcard *.c))


%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

mim: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
		rm -f *.o
		rm -f mim
