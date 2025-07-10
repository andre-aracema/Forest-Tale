#ifndef SPRITES_BOSS_BULLET_H
#define SPRITES_BOSS_BULLET_H

#define BULLET_BOSS_WS 100

#define BULLET_BOSS_ATTACK 8

// estruturas para armazenar sprites do projétil.
struct BulletBossSprites{
    ALLEGRO_BITMAP *sprite;

    ALLEGRO_BITMAP *attack[BULLET_BOSS_ATTACK];
};

extern struct BulletBossSprites bullet_boss_sprites;

// pega um pedaço do sprite.
ALLEGRO_BITMAP *bullet_boss_sprite_cut(ALLEGRO_BITMAP *sheet, int x, int y, int w, int h);

// inicializa as sprites.
void bullet_boss_sprites_init();

// libera memória.
void bullet_boss_sprites_destroy();

#endif