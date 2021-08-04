# Splay Tree implementation Makefile for Scientific Initiation

C_FLAGS := -Wall -pedantic
CC := gcc
RM := rm

.PHONY: $(TARGET)
.PHONY: clean

VPATH:= ./src/ ./obj/ ./include/

# Path for .c , .h and .o Files 
SRC_PATH := ./src/
OBJ_PATH := ./obj/
INC_PATH := -I ./include

# Executable Name 
TARGET1 := iterative_exe
# TARGET2 := automatic_exe

# Files to compile
OBJ_iterative := testaIterativo.o printTree.o splay.o node.o item.o

# OBJ_automatic := testaAutoma.o printTree.o splay.o node.o item.o

OBJ1 := $(patsubst %,$(OBJ_PATH)%,$(OBJ_iterative))

# OBJ2 := $(patsubst %,$(OBJ_PATH)%,$(OBJ_automatic))

# Build .o first
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@echo [CC] $<
	@$(CC) $(C_FLAGS) -o $@ -c $< $(INC_PATH)


# Build final Binary
# all: $(TARGET1) $(TARGET2)

$(TARGET1):      $(OBJ1)
	@echo [INFO] Creating Binary Executable for Iterative File [$(TARGET1)]
	@$(CC) -o $@ $^

# $(TARGET2):      $(OBJ2)
# 	@echo [INFO] Creating Binary Executable for Automatic File [$(TARGET2)]
# 	@$(CC) -o $@ $^


# Clean all the object files and the binary
clean:   
	@echo "[Cleaning]"
	@$(RM) -rfv $(OBJ_PATH)*
	@$(RM) -rfv $(TARGET1)
	@$(RM) -rfv $(TARGET2)