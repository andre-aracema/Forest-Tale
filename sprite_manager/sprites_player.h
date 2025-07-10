#ifndef SPRITES_PLAYER_H
#define SPRITES_PLAYER_H

#define PLAYER_WS 128
#define PLAYER_HS 128

#define PLAYER_IDLE 2
#define PLAYER_WALK 8
#define PLAYER_CROUCHED 6
#define PLAYER_JUMP 8
#define PLAYER_DIED 8
#define PLAYER_ATTACK 8

#define HEART_SIZE 48
#define PLAYER_HEART 5

#define PLAYER_F 3

// estruturas para armazenar sprites do personagem.
struct PlayerSpritesRight{
    ALLEGRO_BITMAP *right;

    ALLEGRO_BITMAP *idle[PLAYER_IDLE];
    ALLEGRO_BITMAP *walk[PLAYER_WALK];
    ALLEGRO_BITMAP *crouched[PLAYER_CROUCHED];
    ALLEGRO_BITMAP *jump[PLAYER_JUMP];
    ALLEGRO_BITMAP *died[PLAYER_DIED];
    ALLEGRO_BITMAP *attack[PLAYER_ATTACK];
};

struct PlayerSpritesLeft{
    ALLEGRO_BITMAP *left;

    ALLEGRO_BITMAP *idle[PLAYER_IDLE];
    ALLEGRO_BITMAP *walk[PLAYER_WALK];
    ALLEGRO_BITMAP *crouched[PLAYER_CROUCHED];
    ALLEGRO_BITMAP *jump[PLAYER_JUMP];
    ALLEGRO_BITMAP *died[PLAYER_DIED];
    ALLEGRO_BITMAP *attack[PLAYER_ATTACK];
};

struct PlayerSpritesLives{
    ALLEGRO_BITMAP *lives;
    ALLEGRO_BITMAP *fundo1;
    ALLEGRO_BITMAP *fundo2;
    ALLEGRO_BITMAP *fundo3;

    ALLEGRO_BITMAP *heart[PLAYER_HEART];
    ALLEGRO_BITMAP *f[PLAYER_F];
};

extern struct PlayerSpritesRight player_sprites_r;
extern struct PlayerSpritesLeft player_sprites_l;
extern struct PlayerSpritesLives player_sprites_h;

// pega um pedaço do sprite.
ALLEGRO_BITMAP *player_sprite_cut(ALLEGRO_BITMAP *sheet, int x, int y, int w, int h);

// inicializa as sprites.
void player_sprites_init();

// libera memória.
void player_sprites_destroy();

#endif