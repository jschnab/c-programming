OBJS = sounds.c

CC = gcc

COMPILER_FLAGS = -Wall -DNDEBUG

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer

OBJ_NAME = sounds

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
