# Splay Tree implementation Makefile for Scientific Initiation

# Compiler Link
CC=gcc

#Flags for compiler
CC_FLAGS=-Wall -ansi -pedantic

# Command used at clean target
RM = rm -rf

# Object Files
OBJS1 		= testaAutoma.o printTree.o splay.o node.o item.o
OBJS2 		= testaIterativo.o printTree.o splay.o node.o item.o
OBJS3		= criateste.o
EXEC 		= testaAutoma testaIterativo criateste

# ----------------------------------------------------------
all: $(EXEC)

criateste: $(OBJS3)
	$(CC) $(OBJS3) -o criateste -lm

testaAutoma: $(OBJS1)
	$(CC) $(OBJS1) -o testaAutoma -lm

testaIterativo: $(OBJS2)
	$(CC) $(OBJS2) -o testaIterativo -lm

testaAutoma.o: testaAutoma.c splay.o printTree.o node.o item.o
	$(CC) $(CFLAGS) -c testaAutoma.c

testaIterativo.o: testaIterativo.c splay.o printTree.o node.o item.o
	$(CC) $(CFLAGS) -c testaIterativo.c

splay.o: splay.c splay.h
	$(CC) $(CFLAGS) -c splay.c

printTree.o: printTree.c printTree.h
	$(CC) $(CFLAGS) -c printTree.c

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

item.o: item.c item.h
	$(CC) $(CFLAGS) -c item.c

clean:
	$(RM) *.o *~ $(EXEC)

