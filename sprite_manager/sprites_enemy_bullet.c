#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "system.h"
#include "sprites_enemy_bullet.h"

struct BulletEnemySpritesRight bullet_enemy_sprites_r;
struct BulletEnemySpritesLeft bullet_enemy_sprites_l;

ALLEGRO_BITMAP *bullet_enemy_sprite_cut(ALLEGRO_BITMAP *sheet, int x, int y, int w, int h){
    ALLEGRO_BITMAP *sprite = al_create_sub_bitmap(sheet, x, y, w, h);
    must_init(sprite, "sprite");
    return sprite;
}

void bullet_enemy_sprites_init(){
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    bullet_enemy_sprites_l.left = al_load_bitmap("assets/sprites/bullet/bullet_enemy_left.png");
    bullet_enemy_sprites_r.right = al_load_bitmap("assets/sprites/bullet/bullet_enemy_right.png");

    // lado direito.
    for(int i = 0; i < BULLET_ENEMY_ATTACK; i++)
        bullet_enemy_sprites_r.attack[i] = bullet_enemy_sprite_cut(bullet_enemy_sprites_r.right, BULLET_ENEMY_WS * i, BULLET_ENEMY_HS * 0, BULLET_ENEMY_WS, BULLET_ENEMY_HS);

    // lado esquerdo.
    for(int i = 0; i < BULLET_ENEMY_ATTACK; i++){
        int j = 9 - i;
        bullet_enemy_sprites_l.attack[i] = bullet_enemy_sprite_cut(bullet_enemy_sprites_l.left, BULLET_ENEMY_WS * j, BULLET_ENEMY_HS * 0, BULLET_ENEMY_WS, BULLET_ENEMY_HS);
    }
}

void bullet_enemy_sprites_destroy(){
    for(int i = 0; i < BULLET_ENEMY_ATTACK; i++){
        if(bullet_enemy_sprites_r.attack[i])
            al_destroy_bitmap(bullet_enemy_sprites_r.attack[i]);
        if(bullet_enemy_sprites_l.attack[i])
            al_destroy_bitmap(bullet_enemy_sprites_l.attack[i]);
    }

    if(bullet_enemy_sprites_r.right)
        al_destroy_bitmap(bullet_enemy_sprites_r.right);

    if(bullet_enemy_sprites_l.left)
        al_destroy_bitmap(bullet_enemy_sprites_l.left);
}