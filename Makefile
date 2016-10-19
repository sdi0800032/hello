CC = gcc
CFLAGS = -Wall -g 
HEADER = Cstruct.h
SOURCE = cosinetest.c Cstruct.c
OUT = cosine
OBJS = cosinetest.o Cstruct.o

all:	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o cosine -lm

cosinetest.o: cosinetest.c
	$(CC) $(CFLAGS) -c cosinetest.c

Cstruct.o: Cstruct.c
	$(CC) $(CFLAGS) -c Cstruct.c

clean:
	rm -rf *o $(OUT)
