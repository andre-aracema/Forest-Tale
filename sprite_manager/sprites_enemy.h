#ifndef SPRITES_ENEMY_H
#define SPRITES_ENEMY_H

#define ENEMY_WS 128
#define ENEMY_HS 128

#define ENEMY_IDLE 2
#define ENEMY_WALK 8
#define ENEMY_DIED 8
#define ENEMY_ATTACK 8

// estruturas para armazenar sprites do personagem.
struct EnemySpritesRight{
    ALLEGRO_BITMAP *right;

    ALLEGRO_BITMAP *idle[ENEMY_IDLE];
    ALLEGRO_BITMAP *walk[ENEMY_WALK];
    ALLEGRO_BITMAP *died[ENEMY_DIED];
    ALLEGRO_BITMAP *attack[ENEMY_ATTACK];
};

struct EnemySpritesLeft{
    ALLEGRO_BITMAP *left;

    ALLEGRO_BITMAP *idle[ENEMY_IDLE];
    ALLEGRO_BITMAP *walk[ENEMY_WALK];
    ALLEGRO_BITMAP *died[ENEMY_DIED];
    ALLEGRO_BITMAP *attack[ENEMY_ATTACK];
};

extern struct EnemySpritesRight enemy_sprites_r;
extern struct EnemySpritesLeft enemy_sprites_l;

// pega um pedaço do sprite.
ALLEGRO_BITMAP *enemy_sprite_cut(ALLEGRO_BITMAP *sheet, int x, int y, int w, int h);

// inicializa as sprites.
void enemy_sprites_init();

// libera memória.
void enemy_sprites_destroy();

#endif