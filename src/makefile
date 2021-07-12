CC       = gcc
CPPFLAGS =
CFLAGS   = -Wall -Wextra -O2 -std=c11 -g
LDFLAGS  =

.PHONY: all clean

all: similar_lines

similar_lines: main.o parsing.o comparingLines.o
	gcc -o similar_lines comparingLines.o parsing.o main.o
comparingLines.o: comparingLines.c comparingLines.h
parsing.o: parsing.c parsing.h
main.o: main.c comparingLines.h parsing.h structures.h

clean:
	rm -f *.o similar_lines
