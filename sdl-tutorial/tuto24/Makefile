OBJS = framerate.c

CC = gcc

COMPILER_FLAGS = -Wall -DNDEBUG

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

OBJ_NAME = framerate

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
