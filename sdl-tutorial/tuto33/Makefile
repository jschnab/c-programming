OBJS = file_rw.c

CC = gcc

COMPILER_FLAGS = -Wall -DNDEBUG

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

OBJ_NAME = file_rw

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
