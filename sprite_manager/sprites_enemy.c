#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "system.h"
#include "sprites_enemy.h"

struct EnemySpritesRight enemy_sprites_r;
struct EnemySpritesLeft enemy_sprites_l;

ALLEGRO_BITMAP *enemy_sprite_cut(ALLEGRO_BITMAP *sheet, int x, int y, int w, int h){
    ALLEGRO_BITMAP *sprite = al_create_sub_bitmap(sheet, x, y, w, h);
    must_init(sprite, "sprite");
    return sprite;
}

void enemy_sprites_init(){
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    enemy_sprites_l.left = al_load_bitmap("assets/sprites/enemy/enemy_left.png");
    enemy_sprites_r.right = al_load_bitmap("assets/sprites/enemy/enemy_right.png");

    // lado direito.
    for(int i = 0; i < ENEMY_IDLE; i++)
        enemy_sprites_r.idle[i] = enemy_sprite_cut(enemy_sprites_r.right, ENEMY_WS * i, ENEMY_HS * 0, ENEMY_WS, ENEMY_HS);
    for(int i = 0; i < ENEMY_WALK; i++)
        enemy_sprites_r.walk[i] = enemy_sprite_cut(enemy_sprites_r.right, ENEMY_WS * i, ENEMY_HS * 3, ENEMY_WS, ENEMY_HS);
    for(int i = 0; i < ENEMY_ATTACK; i++)
        enemy_sprites_r.attack[i] = enemy_sprite_cut(enemy_sprites_r.right, ENEMY_WS * i, ENEMY_HS * 8, ENEMY_WS, ENEMY_HS);
    for(int i = 0; i < ENEMY_DIED; i++)
        enemy_sprites_r.died[i] = enemy_sprite_cut(enemy_sprites_r.right, ENEMY_WS * i, ENEMY_HS * 7, ENEMY_WS, ENEMY_HS);

    // lado esquerdo.
    for(int i = 0; i < ENEMY_IDLE; i++){
        int j = 7 - i;
        enemy_sprites_l.idle[i] = enemy_sprite_cut(enemy_sprites_l.left, ENEMY_WS * j, ENEMY_HS * 0, ENEMY_WS, ENEMY_HS);
    }
    for(int i = 0; i < ENEMY_WALK; i++){
        int j = 7 - i;
        enemy_sprites_l.walk[i] = enemy_sprite_cut(enemy_sprites_l.left, ENEMY_WS * j, ENEMY_HS * 3, ENEMY_WS, ENEMY_HS);
    }
    for(int i = 0; i < ENEMY_ATTACK; i++){
        int j = 7 - i;
        enemy_sprites_l.attack[i] = enemy_sprite_cut(enemy_sprites_l.left, ENEMY_WS * j, ENEMY_HS * 8, ENEMY_WS, ENEMY_HS);
    }
    for(int i = 0; i < ENEMY_DIED; i++){
        int j = 7 - i;
        enemy_sprites_l.died[i] = enemy_sprite_cut(enemy_sprites_l.left, ENEMY_WS * j, ENEMY_HS * 7, ENEMY_WS, ENEMY_HS);
    }
}

void enemy_sprites_destroy(){
    for(int i = 0; i < ENEMY_IDLE; i++){
        if(enemy_sprites_r.idle[i])
            al_destroy_bitmap(enemy_sprites_r.idle[i]);
        if(enemy_sprites_l.idle[i])
            al_destroy_bitmap(enemy_sprites_l.idle[i]);
    }
    for(int i = 0; i < ENEMY_WALK; i++){
        if(enemy_sprites_r.idle[i])
            al_destroy_bitmap(enemy_sprites_r.walk[i]);
        if(enemy_sprites_l.idle[i])
            al_destroy_bitmap(enemy_sprites_l.walk[i]);
    }
    for(int i = 0; i < ENEMY_ATTACK; i++){
        if(enemy_sprites_r.idle[i])
            al_destroy_bitmap(enemy_sprites_r.attack[i]);
        if(enemy_sprites_l.idle[i])
            al_destroy_bitmap(enemy_sprites_l.attack[i]);
    }
    for(int i = 0; i < ENEMY_DIED; i++){
        if(enemy_sprites_r.idle[i])
            al_destroy_bitmap(enemy_sprites_r.died[i]);
        if(enemy_sprites_l.idle[i])
            al_destroy_bitmap(enemy_sprites_l.died[i]);
    }
}