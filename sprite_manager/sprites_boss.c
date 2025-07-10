#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "system.h"
#include "sprites_boss.h"

struct BossSpritesRight boss_sprites_r;
struct BossSpritesLeft boss_sprites_l;

ALLEGRO_BITMAP *boss_sprite_cut(ALLEGRO_BITMAP *sheet, int x, int y, int w, int h){
    ALLEGRO_BITMAP *sprite = al_create_sub_bitmap(sheet, x, y, w, h);
    must_init(sprite, "sprite");
    return sprite;
}

void boss_sprites_init(){
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    // lado direito.
    boss_sprites_r.attack1_s = al_load_bitmap("assets/sprites/boss/right/boss_attack1_right.png");
    boss_sprites_r.die_s = al_load_bitmap("assets/sprites/boss/right/boss_die_right.png");
    boss_sprites_r.idle_s = al_load_bitmap("assets/sprites/boss/right/boss_idle_right.png");
    boss_sprites_r.sleep_s = al_load_bitmap("assets/sprites/boss/right/boss_sleep_right.png");
    boss_sprites_r.wakeup_s = al_load_bitmap("assets/sprites/boss/right/boss_wakeup_right.png");
    boss_sprites_r.walk_s = al_load_bitmap("assets/sprites/boss/right/boss_walk_right.png");

    for(int i = 0; i < BOSS_ATTACK1; i++)
        boss_sprites_r.attack1[i] = boss_sprite_cut(boss_sprites_r.attack1_s, BOSS_WS * i, 0, BOSS_WS, BOSS_HS);
    for(int i = 0; i < BOSS_DIE; i++){
        int j = 10 - i;
        boss_sprites_r.die[i] = boss_sprite_cut(boss_sprites_r.die_s, BOSS_WS * j, 0, BOSS_WS, BOSS_HS);
    } 
    for(int i = 0; i < BOSS_IDLE; i++)
        boss_sprites_r.idle[i] = boss_sprite_cut(boss_sprites_r.idle_s, BOSS_WS * i, 0, BOSS_WS, BOSS_HS);
    for(int i = 0; i < BOSS_SLEEP; i++)
        boss_sprites_r.sleep[i] = boss_sprite_cut(boss_sprites_r.sleep_s, BOSS_WS * i, 0, BOSS_WS, BOSS_HS);
    for(int i = 0; i < BOSS_WAKEUP; i++)
        boss_sprites_r.wakeup[i] = boss_sprite_cut(boss_sprites_r.wakeup_s, BOSS_WS * i, 0, BOSS_WS, BOSS_HS);
    for(int i = 0; i < BOSS_WALK; i++)
        boss_sprites_r.walk[i] = boss_sprite_cut(boss_sprites_r.walk_s, BOSS_WS * i, 0, BOSS_WS, BOSS_HS);

    // lado esquerdo.
    boss_sprites_l.attack1_s = al_load_bitmap("assets/sprites/boss/left/boss_attack1_left.png");
    boss_sprites_l.die_s = al_load_bitmap("assets/sprites/boss/left/boss_die_left.png");
    boss_sprites_l.idle_s = al_load_bitmap("assets/sprites/boss/left/boss_idle_left.png");
    boss_sprites_l.sleep_s = al_load_bitmap("assets/sprites/boss/left/boss_sleep_left.png");
    boss_sprites_l.wakeup_s = al_load_bitmap("assets/sprites/boss/left/boss_wakeup_left.png");
    boss_sprites_l.walk_s = al_load_bitmap("assets/sprites/boss/left/boss_walk_left.png");

    for(int i = 0; i < BOSS_ATTACK1; i++)
        boss_sprites_l.attack1[i] = boss_sprite_cut(boss_sprites_l.attack1_s, BOSS_WS * i, 0, BOSS_WS, BOSS_HS);
    for(int i = 0; i < BOSS_DIE; i++)
        boss_sprites_l.die[i] = boss_sprite_cut(boss_sprites_l.die_s, BOSS_WS * i, 0, BOSS_WS, BOSS_HS); 
    for(int i = 0; i < BOSS_IDLE; i++)
        boss_sprites_l.idle[i] = boss_sprite_cut(boss_sprites_l.idle_s, BOSS_WS * i, 0, BOSS_WS, BOSS_HS);
    for(int i = 0; i < BOSS_SLEEP; i++)
        boss_sprites_l.sleep[i] = boss_sprite_cut(boss_sprites_l.sleep_s, BOSS_WS * i, 0, BOSS_WS, BOSS_HS);
    for(int i = 0; i < BOSS_WAKEUP; i++)
        boss_sprites_l.wakeup[i] = boss_sprite_cut(boss_sprites_l.wakeup_s, BOSS_WS * i, 0, BOSS_WS, BOSS_HS);
    for(int i = 0; i < BOSS_WALK; i++)
        boss_sprites_l.walk[i] = boss_sprite_cut(boss_sprites_l.walk_s, BOSS_WS * i, 0, BOSS_WS, BOSS_HS);
}

void boss_sprites_destroy(){
    for(int i = 0; i < BOSS_ATTACK1; i++){
        if(boss_sprites_r.attack1[i])
            al_destroy_bitmap(boss_sprites_r.attack1[i]);
        if(boss_sprites_l.attack1[i])
            al_destroy_bitmap(boss_sprites_l.attack1[i]);
    }
    for(int i = 0; i < BOSS_DIE; i++){
        if(boss_sprites_r.die[i])
            al_destroy_bitmap(boss_sprites_r.die[i]);
        if(boss_sprites_l.die[i])
            al_destroy_bitmap(boss_sprites_l.die[i]);
    }
    for(int i = 0; i < BOSS_IDLE; i++){
        if(boss_sprites_r.idle[i])
            al_destroy_bitmap(boss_sprites_r.idle[i]);
        if(boss_sprites_l.idle[i])
            al_destroy_bitmap(boss_sprites_l.idle[i]);
    }
    for(int i = 0; i < BOSS_SLEEP; i++){
        if(boss_sprites_r.sleep[i])
            al_destroy_bitmap(boss_sprites_r.sleep[i]);
        if(boss_sprites_l.sleep[i])
            al_destroy_bitmap(boss_sprites_l.sleep[i]);
    }
    for(int i = 0; i < BOSS_WAKEUP; i++){
        if(boss_sprites_r.wakeup[i])
            al_destroy_bitmap(boss_sprites_r.wakeup[i]);
        if(boss_sprites_l.wakeup[i])    
            al_destroy_bitmap(boss_sprites_l.wakeup[i]);
    }
    for(int i = 0; i < BOSS_WALK; i++){
        if(boss_sprites_r.walk[i])
            al_destroy_bitmap(boss_sprites_r.walk[i]);
        if(boss_sprites_l.walk[i])
            al_destroy_bitmap(boss_sprites_l.walk[i]);
    }
    
    if(boss_sprites_r.attack1_s)
        al_destroy_bitmap(boss_sprites_r.attack1_s);
    if(boss_sprites_r.die_s)
        al_destroy_bitmap(boss_sprites_r.die_s);
    if(boss_sprites_r.idle_s)
        al_destroy_bitmap(boss_sprites_r.idle_s);
    if(boss_sprites_r.sleep_s)
        al_destroy_bitmap(boss_sprites_r.sleep_s);
    if(boss_sprites_r.wakeup_s)
        al_destroy_bitmap(boss_sprites_r.wakeup_s);
    if(boss_sprites_r.walk_s)
        al_destroy_bitmap(boss_sprites_r.walk_s);
    if(boss_sprites_l.attack1_s)
        al_destroy_bitmap(boss_sprites_l.attack1_s);
    if(boss_sprites_l.die_s)
        al_destroy_bitmap(boss_sprites_l.die_s);
    if(boss_sprites_l.idle_s)
        al_destroy_bitmap(boss_sprites_l.idle_s);
    if(boss_sprites_l.sleep_s)
        al_destroy_bitmap(boss_sprites_l.sleep_s);
    if(boss_sprites_l.wakeup_s)
        al_destroy_bitmap(boss_sprites_l.wakeup_s);
    if(boss_sprites_l.walk_s)
        al_destroy_bitmap(boss_sprites_l.walk_s);
}