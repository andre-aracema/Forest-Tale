#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "system.h"
#include "sprites_boss_bullet.h"

struct BulletBossSprites bullet_boss_sprites;

ALLEGRO_BITMAP *bullet_boss_sprite_cut(ALLEGRO_BITMAP *sheet, int x, int y, int w, int h){
    ALLEGRO_BITMAP *sprite = al_create_sub_bitmap(sheet, x, y, w, h);
    must_init(sprite, "sprite");
    return sprite;
}

void bullet_boss_sprites_init(){
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    bullet_boss_sprites.sprite = al_load_bitmap("assets/sprites/bullet/bullet_boss.png");

    // lado direito.
    for(int i = 0; i < BULLET_BOSS_ATTACK; i++)
        bullet_boss_sprites.attack[i] = bullet_boss_sprite_cut(bullet_boss_sprites.sprite, BULLET_BOSS_WS * i, 0, BULLET_BOSS_WS, BULLET_BOSS_WS);

}

void bullet_boss_sprites_destroy(){
    for(int i = 0; i < BULLET_BOSS_ATTACK; i++){
        if(bullet_boss_sprites.attack[i])
        al_destroy_bitmap(bullet_boss_sprites.attack[i]);
    }

    if(bullet_boss_sprites.sprite)
        al_destroy_bitmap(bullet_boss_sprites.sprite);

}