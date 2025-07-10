#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "enemy.h"
#include "camera.h"
#include "background.h"
#include "boss.h"
#include "shot.h"
#include "item.h"
#include "player.h"
#include "display.h"
#include "render.h"


void render_menu(ALLEGRO_BITMAP *menu, struct Display *display){
    background_state_update(menu, display);
}

void render_settings(ALLEGRO_BITMAP *settings, struct Display *display){
    background_state_update(settings, display);
}

void render_pause(ALLEGRO_BITMAP *pause, struct Display *display){
    background_state_update(pause, display);
}

void render_gameover(ALLEGRO_BITMAP *gameover, struct Display *display){
    background_state_update(gameover, display);
}

void render_victory(ALLEGRO_BITMAP *victory, struct Display *display){
    background_state_update(victory, display);
}

void render_game(ALLEGRO_BITMAP *game, ALLEGRO_FONT *font, struct Display *display, struct Player *player,
                struct Item *items, struct ShotManager *pistol, struct Boss *boss,  int *camera_x, float time){

    *camera_x = camera_update(player, display);
    background_game_update(game, display, *camera_x);
    al_draw_textf(font, al_map_rgb(255, 255, 255), display->x_text, display->y_text, 0, "SCORE: %d", player->score);
    player_status_draw(player, items, time);
    item_draw(items, *camera_x, time);
    enemy_shots_draw(pistol, *camera_x);
    enemies_draw(*camera_x);
    boss_draw(boss, *camera_x);
    if(!boss->sleep)
        boss_shots_draw(pistol, *camera_x);
    player_shots_draw(pistol, *camera_x);
    player_draw(player, display, *camera_x);
}
