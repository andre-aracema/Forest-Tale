#ifndef SHOT_H
#define SHOT_H

#define SHOT_PLAYER_SPEED 30
#define SHOT_PLAYER_DELAY 20
#define SHOT_ENEMY_SPEED 15
#define SHOT_ENEMY_DELAY 64
#define SHOT_BOSS_SPEED 20
#define SHOT_BOSS_DELAY 45
#define SHOTS_MAX 36

struct Shot{
    int x, y;                             // posição do projétil.
    int dx, dy;                           // direção/velocidade do projétil.
    int used;                             // tiro ativo.
    int width, height;                    // tamanho do tiro.
    int col_w, col_h;                     // área de colisão.
    int anim_frame, anim_counter;         // auxiliar na hora de desenhar os sprites.
    int offset_up;                        // auxiliar no hitbox.
};

struct ShotManager{
    struct Shot shots[SHOTS_MAX];         // quantidade de balas do player.
    struct Shot shots_enemy[SHOTS_MAX];   // quantidade de balas dos inimigos.
    struct Shot shots_boss[SHOTS_MAX];    // quantidade de balas do boss.
};

struct Enemy;
struct Display;
struct Player;
struct Boss;

// inicializa os projéteis.
void shots_init(struct ShotManager *pistol, struct Player *player, struct Boss *boss);

//---------------------PLAYER--------------------------------------------//

// adiciona o disparo.
void player_shot_add(struct ShotManager *pistol, int x, int y, int dx, int dy, int width, int height);

// atualiza os disparos.
void player_shots_update(struct ShotManager *pistol, struct Display *disp, struct Player *player, struct Boss *boss, int camera_x);

// atualiza disparos feitos pelo player.
void player_shot_update(struct ShotManager *pistol, struct Player *player);

// desenha os projéteis na tela.
void player_shots_draw(struct ShotManager *pistol, int camera_x);

//-----------------------ENEMY--------------------------------------------//

// adidiona o disparo.
void enemy_shot_add(struct ShotManager *pistol, int x, int y, int dx, int dy, int width, int height);

// atualiza os disparos.
void enemy_shots_update(struct ShotManager *pistol, struct Display *disp, struct Player *player, int camera_x);

// atualiza disparos feitos pelo inimigo.
void enemy_shot_update(struct ShotManager *pistol, struct Enemy *enemy);

// desenha os projéteis na tela.
void enemy_shots_draw(struct ShotManager *pistol, int camera_x);

//-----------------------BOSS------------------------------------------------//

// adiciona o disparo.
void boss_shot_add(struct ShotManager *pistol, int x, int y, int dx, int dy, int width, int height);

// atualiza os disparos.
void boss_shots_update(struct ShotManager *pistol, struct Display *disp, struct Player *player, struct Boss *boss, int camera_x);

// atualiza disparos feitos pelo boss.
void boss_shot_update(struct ShotManager *pistol, struct Boss *boss, struct Player *player);

// desenha os projéteis na tela.
void boss_shots_draw(struct ShotManager *pistol, int camera_x);

#endif