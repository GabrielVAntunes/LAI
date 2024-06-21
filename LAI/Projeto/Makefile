
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O2 -lncurses -lm
SOURCES = *.c

all: rogue run clean

rogue: 
	$(CC) $(SOURCES) $(CFLAGS) -o rogue

run:
	./rogue

clean:
	rm rogue