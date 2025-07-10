#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "system.h"
#include "sprites_bullet.h"

struct BulletSpritesRight bullet_sprites_r;
struct BulletSpritesLeft bullet_sprites_l;
struct BulletSpritesUp bullet_sprites_u;

ALLEGRO_BITMAP *bullet_sprite_cut(ALLEGRO_BITMAP *sheet, int x, int y, int w, int h){
    ALLEGRO_BITMAP *sprite = al_create_sub_bitmap(sheet, x, y, w, h);
    must_init(sprite, "sprite");
    return sprite;
}

void bullet_sprites_init(){
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    bullet_sprites_l.left = al_load_bitmap("assets/sprites/bullet/bullet_left.png");
    bullet_sprites_r.right = al_load_bitmap("assets/sprites/bullet/bullet_right.png");
    bullet_sprites_u.up = al_load_bitmap("assets/sprites/bullet/bullet_up.png");

    // lado direito.
    for(int i = 0; i < BULLET_ATTACK; i++)
        bullet_sprites_r.attack[i] = bullet_sprite_cut(bullet_sprites_r.right, BULLET_WS * i, BULLET_HS * 0, BULLET_WS, BULLET_HS);

    // lado esquerdo.
    for(int i = 0; i < BULLET_ATTACK; i++){
        int j = 9 - i;
        bullet_sprites_l.attack[i] = bullet_sprite_cut(bullet_sprites_l.left, BULLET_WS * j, BULLET_HS * 0, BULLET_WS, BULLET_HS);
    }

    // para cima.
    for(int i = 0; i < BULLET_ATTACK_UP; i++){
        int j = 3 - i;
        if(j >= 0)
            bullet_sprites_u.attack[i] = bullet_sprite_cut(bullet_sprites_u.up, BULLET_UP_WS * 0, BULLET_UP_WS * j, BULLET_UP_WS, BULLET_UP_HS);
        else{
            int k = 3 + (j + 1);
            bullet_sprites_u.attack[i] = bullet_sprite_cut(bullet_sprites_u.up, BULLET_UP_WS * 1, BULLET_UP_WS * k, BULLET_UP_WS, BULLET_UP_HS);
        }
    }
}

void bullet_sprites_destroy(){
    for(int i = 0; i < BULLET_ATTACK; i++){
        if(bullet_sprites_r.attack[i])
            al_destroy_bitmap(bullet_sprites_r.attack[i]);
        if(bullet_sprites_l.attack[i])
            al_destroy_bitmap(bullet_sprites_l.attack[i]);
    }
    for(int i = 0; i < BULLET_ATTACK_UP; i++){
        if(bullet_sprites_u.attack[i])
            al_destroy_bitmap(bullet_sprites_u.attack[i]);
    }

    if(bullet_sprites_r.right)
        al_destroy_bitmap(bullet_sprites_r.right);

    if(bullet_sprites_l.left)
        al_destroy_bitmap(bullet_sprites_l.left);

    if(bullet_sprites_u.up)
        al_destroy_bitmap(bullet_sprites_u.up);
}