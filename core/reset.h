#ifndef RESET_H
#define RESET_H

struct Player;
struct Display;
struct ButtonGroup;
struct ShotManager;
struct Item;
struct Boss;

// reseta os objetos do 'game'.
void game_reset_init(struct Player **player, struct ShotManager *pistol, struct Display *display, struct Item *items, struct Boss *boss, int *camera_x);

// ajusta a resolução do display, reestruturando as demais estruturas.
void display_reset(struct Display *display, struct ButtonGroup *buttons, struct Player **player, struct ShotManager *pistol, struct Item *items, struct Boss *boss, int fullscreen, int *camera_x);

#endif