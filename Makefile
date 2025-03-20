CC = clang
CFLAGS = -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE -g
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lSDL2_mixer

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
obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure obj/ directory exists
obj:
	mkdir -p obj

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run
