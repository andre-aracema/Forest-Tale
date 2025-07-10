TARGET = jogo
SRC = main.c core/*.c entities/*.c graphics/*.c sprite_manager/*.c ui/*.c
INCLUDES = -Icore -Ientities -Igraphics -Isprite_manager -Iui
ALLEGRO = $(shell pkg-config --cflags --libs allegro-5 allegro_font-5 allegro_image-5 allegro_ttf-5 allegro_primitives-5)
CFLAGS = -Wall -Wextra

all:
	gcc $(SRC) $(INCLUDES) $(CFLAGS) $(ALLEGRO) -o $(TARGET) -lm

clean:
	rm -r $(TARGET)