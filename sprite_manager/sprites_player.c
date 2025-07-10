#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "system.h"
#include "sprites_player.h"

struct PlayerSpritesRight player_sprites_r;
struct PlayerSpritesLeft player_sprites_l;
struct PlayerSpritesLives player_sprites_h;

ALLEGRO_BITMAP *player_sprite_cut(ALLEGRO_BITMAP *sheet, int x, int y, int w, int h){
    ALLEGRO_BITMAP *sprite = al_create_sub_bitmap(sheet, x, y, w, h);
    must_init(sprite, "sprite");
    return sprite;
}

void player_sprites_init(){
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    player_sprites_l.left = al_load_bitmap("assets/sprites/player/player_left.png");
    player_sprites_r.right = al_load_bitmap("assets/sprites/player/player_right.png");
    player_sprites_h.lives = al_load_bitmap("assets/sprites/player/hearts.png");
    player_sprites_h.fundo1 = al_load_bitmap("assets/sprites/player/fundo1.png");
    player_sprites_h.fundo2 = al_load_bitmap("assets/sprites/player/fundo2.png");
    player_sprites_h.fundo3 = al_load_bitmap("assets/sprites/player/fundo3.png");

    // lado direito.
    for(int i = 0; i < PLAYER_IDLE; i++)
        player_sprites_r.idle[i] = player_sprite_cut(player_sprites_r.right, PLAYER_WS * i, PLAYER_HS * 0, PLAYER_WS, PLAYER_HS);
    for(int i = 0; i < PLAYER_WALK; i++)
        player_sprites_r.walk[i] = player_sprite_cut(player_sprites_r.right, PLAYER_WS * i, PLAYER_HS * 3, PLAYER_WS, PLAYER_HS);
    for(int i = 0; i < PLAYER_JUMP; i++)
        player_sprites_r.jump[i] = player_sprite_cut(player_sprites_r.right, PLAYER_WS * i, PLAYER_HS * 5, PLAYER_WS, PLAYER_HS);
    for(int i = 0; i < PLAYER_DIED; i++)
        player_sprites_r.died[i] = player_sprite_cut(player_sprites_r.right, PLAYER_WS * i, PLAYER_HS * 7, PLAYER_WS, PLAYER_HS);
    for(int i = 0; i < PLAYER_ATTACK; i++)
        player_sprites_r.attack[i] = player_sprite_cut(player_sprites_r.right, (PLAYER_WS * i), PLAYER_HS * 8, PLAYER_WS, PLAYER_HS);
    for(int i = 0; i < PLAYER_CROUCHED; i++)
        player_sprites_r.crouched[i] = player_sprite_cut(player_sprites_r.right, PLAYER_WS * i, PLAYER_HS * 4, PLAYER_WS, PLAYER_HS);

    // lado esquerdo.
    for(int i = 0; i < PLAYER_IDLE; i++){
        int j = 7 - i;
        player_sprites_l.idle[i] = player_sprite_cut(player_sprites_l.left, PLAYER_WS * j, PLAYER_HS * 0, PLAYER_WS, PLAYER_HS);
    }
    for(int i = 0; i < PLAYER_WALK; i++){
        int j = 7 - i;
        player_sprites_l.walk[i] = player_sprite_cut(player_sprites_l.left, PLAYER_WS * j, PLAYER_HS * 3, PLAYER_WS, PLAYER_HS);
    }
    for(int i = 0; i < PLAYER_JUMP; i++){
        int j = 7 - i;
        player_sprites_l.jump[i] = player_sprite_cut(player_sprites_l.left, PLAYER_WS * j, PLAYER_HS * 5, PLAYER_WS, PLAYER_HS);
    }
    for(int i = 0; i < PLAYER_DIED; i++){
        int j = 7 - i;
        player_sprites_l.died[i] = player_sprite_cut(player_sprites_l.left, PLAYER_WS * j, PLAYER_HS * 7, PLAYER_WS, PLAYER_HS);
    }
    for(int i = 0; i < PLAYER_ATTACK; i++){
        int j = 7 - i;
        player_sprites_l.attack[i] = player_sprite_cut(player_sprites_l.left, PLAYER_WS * j, PLAYER_HS * 8, PLAYER_WS, PLAYER_HS);
    }
    for(int i = 0; i < PLAYER_CROUCHED; i++){           
        int j = 7 - i;
        player_sprites_l.crouched[i] = player_sprite_cut(player_sprites_l.left, PLAYER_WS * j, PLAYER_HS * 4, PLAYER_WS, PLAYER_HS);
    }

    // corações.
    for(int i = 0; i < PLAYER_HEART; i++)
        player_sprites_h.heart[i] = player_sprite_cut(player_sprites_h.lives, HEART_SIZE * i, HEART_SIZE * 0, HEART_SIZE, HEART_SIZE);

    // quadro de fundo do personagem.
    player_sprites_h.f[0] = player_sprites_h.fundo1;
    player_sprites_h.f[1] = player_sprites_h.fundo2;
    player_sprites_h.f[2] = player_sprites_h.fundo3;
}

void player_sprites_destroy(){
    for(int i = 0; i < PLAYER_IDLE; i++){
        if(player_sprites_r.idle[i])
            al_destroy_bitmap(player_sprites_r.idle[i]);
        if(player_sprites_l.idle[i])
            al_destroy_bitmap(player_sprites_l.idle[i]);
    }
    for(int i = 0; i < PLAYER_WALK; i++){
        if(player_sprites_r.walk[i])
            al_destroy_bitmap(player_sprites_r.walk[i]);
        if(player_sprites_l.walk[i])   
            al_destroy_bitmap(player_sprites_l.walk[i]);
    }
    for(int i = 0; i < PLAYER_JUMP; i++){
        if(player_sprites_r.jump[i])
            al_destroy_bitmap(player_sprites_r.jump[i]);
        if(player_sprites_l.jump[i])
            al_destroy_bitmap(player_sprites_l.jump[i]);
    }
    for(int i = 0; i < PLAYER_DIED; i++){
        if(player_sprites_r.died[i])
            al_destroy_bitmap(player_sprites_r.died[i]);
        if(player_sprites_l.died[i])
            al_destroy_bitmap(player_sprites_l.died[i]);
    }
    for(int i = 0; i < PLAYER_ATTACK; i++){
        if(player_sprites_r.attack[i])
            al_destroy_bitmap(player_sprites_r.attack[i]);
        if(player_sprites_l.attack[i])
            al_destroy_bitmap(player_sprites_l.attack[i]);
    }
    for(int i = 0; i < PLAYER_CROUCHED - 1; i++){
        if(player_sprites_r.crouched[i])
            al_destroy_bitmap(player_sprites_r.crouched[i]);
        if(player_sprites_l.crouched[i])
            al_destroy_bitmap(player_sprites_l.crouched[i]);
    }
    for(int i = 0; i < PLAYER_HEART; i++){
        if(player_sprites_h.heart[i])
            al_destroy_bitmap(player_sprites_h.heart[i]);
    }

    if(player_sprites_r.right)
        al_destroy_bitmap(player_sprites_r.right);

    if(player_sprites_l.left)
        al_destroy_bitmap(player_sprites_l.left);
    
    if(player_sprites_h.lives)
        al_destroy_bitmap(player_sprites_h.lives);
    
    if(player_sprites_h.fundo1)
        al_destroy_bitmap(player_sprites_h.fundo1);

    if(player_sprites_h.fundo2)
        al_destroy_bitmap(player_sprites_h.fundo2);

    if(player_sprites_h.fundo3)
        al_destroy_bitmap(player_sprites_h.fundo3);
}