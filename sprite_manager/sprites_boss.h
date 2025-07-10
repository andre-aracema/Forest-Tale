#ifndef SPRITES_BOSS_H
#define SPRITES_BOSS_H

#define BOSS_WS 512
#define BOSS_HS 512

#define BOSS_ATTACK1 8
#define BOSS_DIE 11
#define BOSS_IDLE 9
#define BOSS_WALK 8
#define BOSS_SLEEP 3
#define BOSS_WAKEUP 16

struct BossSpritesRight{
    ALLEGRO_BITMAP *attack1_s;
    ALLEGRO_BITMAP *die_s;
    ALLEGRO_BITMAP *idle_s;
    ALLEGRO_BITMAP *walk_s;
    ALLEGRO_BITMAP *sleep_s;
    ALLEGRO_BITMAP *wakeup_s;

    ALLEGRO_BITMAP *attack1[BOSS_ATTACK1];
    ALLEGRO_BITMAP *die[BOSS_DIE];
    ALLEGRO_BITMAP *idle[BOSS_IDLE];
    ALLEGRO_BITMAP *walk[BOSS_WALK];
    ALLEGRO_BITMAP *sleep[BOSS_SLEEP];
    ALLEGRO_BITMAP *wakeup[BOSS_WAKEUP];
};

struct BossSpritesLeft{
    ALLEGRO_BITMAP *attack1_s;
    ALLEGRO_BITMAP *die_s;
    ALLEGRO_BITMAP *idle_s;
    ALLEGRO_BITMAP *walk_s;
    ALLEGRO_BITMAP *sleep_s;
    ALLEGRO_BITMAP *wakeup_s;

    ALLEGRO_BITMAP *attack1[BOSS_ATTACK1];
    ALLEGRO_BITMAP *die[BOSS_DIE];
    ALLEGRO_BITMAP *idle[BOSS_IDLE];
    ALLEGRO_BITMAP *walk[BOSS_WALK];
    ALLEGRO_BITMAP *sleep[BOSS_SLEEP];
    ALLEGRO_BITMAP *wakeup[BOSS_WAKEUP];
};

extern struct BossSpritesRight boss_sprites_r;
extern struct BossSpritesLeft boss_sprites_l;

// como estamos trabalhando com muitos arquivos, irei fazer de forma genérica.
ALLEGRO_BITMAP *boss_sprite_cut(ALLEGRO_BITMAP *sheet, int x, int y, int w, int h);

// inicializa as sprites.
void boss_sprites_init();

// libera memória.
void boss_sprites_destroy();

#endif