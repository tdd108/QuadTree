CC=gcc
CFLAGS=-std=c17 -pedantic -Wall
LDLIBS= -lm -lMLV

Main : Main.c  Particule.o QuadTree.o Interface.o

Particule.o : Particule.c Particule.h

QuadTree.o : QuadTree.c QuadTree.h

Interface.o : Interface.c Interface.h

.PHONY: clean

clean :
	rm -f *.o

%.o: %.c
	$(CC) $(CFLAGS) $(LDLIBS) -c -o $@ $<