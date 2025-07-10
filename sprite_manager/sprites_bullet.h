#ifndef SPRITES_BULLET_H
#define SPRITES_BULLET_H

#define BULLET_WS 48
#define BULLET_HS 32
#define BULLET_UP_WS 192
#define BULLET_UP_HS 192

#define BULLET_ATTACK 10
#define BULLET_ATTACK_UP 8

// estruturas para armazenar sprites do projétil.
struct BulletSpritesRight{
    ALLEGRO_BITMAP *right;

    ALLEGRO_BITMAP *attack[BULLET_ATTACK];
};

struct BulletSpritesLeft{
    ALLEGRO_BITMAP *left;

    ALLEGRO_BITMAP *attack[BULLET_ATTACK];
};

struct BulletSpritesUp{
    ALLEGRO_BITMAP *up;

    ALLEGRO_BITMAP *attack[BULLET_ATTACK_UP];
};

extern struct BulletSpritesRight bullet_sprites_r;
extern struct BulletSpritesLeft bullet_sprites_l;
extern struct BulletSpritesUp bullet_sprites_u;

// pega um pedaço do sprite.
ALLEGRO_BITMAP *bullet_sprite_cut(ALLEGRO_BITMAP *sheet, int x, int y, int w, int h);

// inicializa as sprites.
void bullet_sprites_init();

// libera memória.
void bullet_sprites_destroy();

#endif