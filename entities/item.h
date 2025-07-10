#ifndef ITEM_H
#define ITEM_H

#define ITEMS_LIVE_MAX 2
#define ITEMS_BOOT_MAX 1
#define ITEMS_TOTAL (ITEMS_BOOT_MAX + ITEMS_LIVE_MAX)

#define ITEM_LIFE 0
#define ITEM_BOOT 1

struct Item{
    int x, y;                 // coordenadas.
    int active;               // se esta na tela ou não.
    ALLEGRO_BITMAP *sprite;   // sprite.
    int type;                 // tipo do item;
};

struct Display;
struct Player;

// inicializa item.
void item_init(struct Item *item, struct Display *disp);

// atualiza o item.
void item_update(struct Item *item, struct Player *player);

// desenha o item.
void item_draw(struct Item *item, int camera_x, float time);

// libera memória.
void item_destroy(struct Item *item);

#endif