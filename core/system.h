#ifndef SYSTEM_H
#define SYSTEM_H

#define KEY_SEEN 1                          // binário 00000001: indica que a tecla foi pressionada nesse frame.
#define KEY_DOWN 2                          // binário 00000010: indica que a tecla está sendo mantida pressionada.
#define MOUSE_MAX 8                         // tamanho máximo de taclas que o mouse poderá ter.

extern unsigned char key[ALLEGRO_KEY_MAX];         
extern unsigned char mouse[MOUSE_MAX];

struct Player;
struct Display;
struct Item;

// inicializa todos os valores do vetor com 0.
void keyboard_mouse_init();

// atualiza as teclas do teclado e do mouse.
void keyboard_mouse_update(ALLEGRO_EVENT* event);

//------------------------------------------------------------------------//

// verifica se uma inicialização foi bem sucedido.
void must_init(bool test, const char *definition);

// inicializa o allegro (init).
void init_allegro();

//------------------------------------------------------------------------//

// carrega bitmaps.
ALLEGRO_BITMAP *load_bitmap(const char *path, const char *debug);

// libera memória alocada.
void cleanup(ALLEGRO_BITMAP *menu, ALLEGRO_BITMAP *background, ALLEGRO_BITMAP *settings, ALLEGRO_BITMAP *gameover,
            ALLEGRO_BITMAP *pause,  ALLEGRO_BITMAP *victory, ALLEGRO_FONT *font, ALLEGRO_TIMER *timer, ALLEGRO_EVENT_QUEUE *queue,
            struct Player *player, struct Display *display, struct Item *items);

#endif