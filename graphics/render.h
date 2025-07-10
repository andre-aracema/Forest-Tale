#ifndef RENDER_H
#define RENDER_H

struct ShotManager;
struct Display;
struct Player;
struct Item;
struct Boss;

// desenha o menu.
void render_menu(ALLEGRO_BITMAP *menu, struct Display *display);

// desenha as configurações.
void render_settings(ALLEGRO_BITMAP *settings, struct Display *display);

// desenha o pause.
void render_pause(ALLEGRO_BITMAP *pause, struct Display *display);

// desenha o gameover.
void render_gameover(ALLEGRO_BITMAP *gameover, struct Display *display);

// desenha a vitória.
void render_victory(ALLEGRO_BITMAP *victory, struct Display *display);

// desenha o jogo.
void render_game(ALLEGRO_BITMAP *game, ALLEGRO_FONT *font, struct Display *display, struct Player *player,
                struct Item *items, struct ShotManager *pistol, struct Boss *boss,  int *camera_x, float time);
            

#endif