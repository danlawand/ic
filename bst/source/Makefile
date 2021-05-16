# BST implementation Makefile for Scientific Initiation

# Object Files
OBJ= 

# Compiler Link
CC=gcc

#Flags for compiler
CC_FLAGS=-Wall -ansi -pedantic

# Command used at clean target
RM = rm -rf

OBJS 		= testa.o bst.o node.o item.o

# ----------------------------------------------------------
testa: $(OBJS)
	$(CC) $(OBJS) -o testa -lm

testa.o: testa.c bst.o node.o item.o
	$(CC) $(CFLAGS) -c testa.c

bst.o: bst.c bst.h
	$(CC) $(CFLAGS) -c bst.c

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

item.o: item.c item.h
	$(CC) $(CFLAGS) -c item.c

clean:
	$(RM) *.o *~ testa

