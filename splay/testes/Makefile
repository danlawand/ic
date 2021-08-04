# Compiler Link
CC=gcc

#Flags for compiler
CC_FLAGS=-Wall -ansi -pedantic

# Command used at clean target
RM = rm -rf

# Object Files
OBJ		= criateste.o

#Binary File
EXEC 		= criateste

# ----------------------------------------------------------
all: $(EXEC)

criateste: $(OBJ)
	$(CC) $(OBJ) -o criateste -lm

clean:
	$(RM) *.o *~ $(EXEC)

