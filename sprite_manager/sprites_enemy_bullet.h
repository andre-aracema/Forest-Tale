#ifndef SPRITES_ENEMY_BULLET_H
#define SPRITES_ENEMY_BULLET_H

#define BULLET_ENEMY_WS 48
#define BULLET_ENEMY_HS 32

#define BULLET_ENEMY_ATTACK 10

// estruturas para armazenar sprites do projétil.
struct BulletEnemySpritesRight{
    ALLEGRO_BITMAP *right;

    ALLEGRO_BITMAP *attack[BULLET_ENEMY_ATTACK];
};

struct BulletEnemySpritesLeft{
    ALLEGRO_BITMAP *left;

    ALLEGRO_BITMAP *attack[BULLET_ENEMY_ATTACK];
};

extern struct BulletEnemySpritesRight bullet_enemy_sprites_r;
extern struct BulletEnemySpritesLeft bullet_enemy_sprites_l;


// pega um pedaço do sprite.
ALLEGRO_BITMAP *bullet_enemy_sprite_cut(ALLEGRO_BITMAP *sheet, int x, int y, int w, int h);

// inicializa as sprites.
void bullet_enemy_sprites_init();

// libera memória.
void bullet_enemy_sprites_destroy();

#endif