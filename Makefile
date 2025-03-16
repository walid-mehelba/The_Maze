CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -Iinc
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lm

# Source and object files
SRCS = src/main.c src/map.c src/player.c src/raycasting.c src/textures.c src/sdl_utils.c
OBJS = $(SRCS:src/%.c=obj/%.o)

# Target executable
TARGET = the_maze

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile source files into object files
obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
