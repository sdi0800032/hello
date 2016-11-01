all: clear clean lsh
CC=gcc
lsh:	lsh.o cosine_eucl.o hash.o Cstruct.o metric.o hamming.o functions.o
	$(CC) -o lsh lsh.o cosine_eucl.o hash.o Cstruct.o metric.o hamming.o functions.o -lm

lsh.o:	lsh.c
	$(CC) -c lsh.c 
cosine_eucl.o:	cosine_eucl.c
	$(CC) -c cosine_eucl.c
hash.o:	hash.c
	$(CC) -c hash.c
Cstruct.o:	Cstruct.c
	$(CC) -c Cstruct.c
metric.o:	metric.c
	$(CC) -c metric.c
hamming.o:	hamming.c
	$(CC) -c hamming.c
functions.o: functions.c
	$(CC) -c functions.c
clear:
	clear

clean:	
	rm -rf *o lsh
