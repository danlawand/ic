# splay implementation Makefile for Scientific Initiation

# Object Files
OBJ= 

# Compiler Link
CC=gcc

#Flags for compiler
CC_FLAGS=-Wall -ansi -pedantic

# Command used at clean target
RM = rm -rf

OBJS1 		= testaAutoma.o splay.o node.o item.o
OBJS2 		= client.o splay.o node.o item.o

# ----------------------------------------------------------

all: testaAutoma client

testaAutoma: $(OBJS1)
	$(CC) $(OBJS1) -o testaAutoma -lm

client: $(OBJS2)
	$(CC) $(OBJS2) -o client -lm

testaAutoma.o: testaAutoma.c splay.o node.o item.o
	$(CC) $(CFLAGS) -c testaAutoma.c

client.o: client.c splay.o node.o item.o
	$(CC) $(CFLAGS) -c client.c

splay.o: splay.c splay.h
	$(CC) $(CFLAGS) -c splay.c

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

item.o: item.c item.h
	$(CC) $(CFLAGS) -c item.c

clean:
	$(RM) *.o *~ testaAutoma

