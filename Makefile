CC = gcc
CFLAGS = -Wall -g -Iinc -I/usr/include/SDL2
LDFLAGS = -L/usr/lib -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

SRC = src/main.c src/map.c src/player.c src/raycasting.c src/sdl_utils.c src/textures.c
OBJ = $(SRC:.c=.o)
TARGET = the_maze

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
