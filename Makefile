CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs) -lm

SRC = raycasting.c player.c map.c sdl_utils.c raycast.c
OBJ = $(SRC:.c=.o)

raycasting: $(OBJ)
	$(CC) $(OBJ) -o raycasting $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) raycasting
