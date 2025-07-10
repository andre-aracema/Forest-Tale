#include <allegro5/allegro.h>
#include "buttons.h"
#include "enemy.h"
#include "shot.h"
#include "player.h"
#include "display.h"
#include "reset.h"
#include "item.h"
#include "boss.h"

void game_reset_init(struct Player **player, struct ShotManager *pistol, struct Display *display, struct Item *items, struct Boss *boss, int *camera_x){
    if(*player)
        player_destroy(*player);
    
    // criando novo player.
    *player = player_create(display);

    // reiniciando/iniciando os inimigos e tiros.
    enemies_init(display);
    shots_init(pistol, *player, boss);
    item_init(items, display);
    boss_init(boss, display);

    // resetando camera.
    *camera_x = 0;
}

void display_reset(struct Display *display, struct ButtonGroup *buttons, struct Player **player, struct ShotManager *pistol, struct Item *items, struct Boss *boss, int fullscreen, int *camera_x){
    display_update(display, fullscreen);

    // atualizando botões.
    buttons_init(buttons->menu, display->width, display->height, MENU_BUTTONS, 0);
    buttons_init(buttons->settings, display->width, display->height, SETTINGS_BUTTONS, 0);
    buttons_init(buttons->pause, display->width, display->height, PAUSE_BUTTONS, 1);
    buttons_init(buttons->gameover, display->width, display->height, GAMEOVER_BUTTONS, 1);
    buttons_init(buttons->victory, display->width, display->height, VICTORY_BUTTONS, 1);

    game_reset_init(player, pistol, display, items, boss, camera_x);
}