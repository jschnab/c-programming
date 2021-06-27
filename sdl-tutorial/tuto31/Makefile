OBJS = scrolling.c

CC = gcc

COMPILER_FLAGS = -Wall -DNDEBUG

LINKER_FLAGS = -lSDL2 -lSDL2_image

OBJ_NAME = scrolling

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
