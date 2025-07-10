#ifndef BOSS_H
#define BOSS_H

#define BOSS_ALIVE -1
#define BOSS_SPEED 10
#define BOSS_LIVE 30
#define BOSS_SPEED_Y 3
#define BOSS_HEIGHT 200
#define BOSS_WIDTH 250

#define BOSS_INITIAL_OFFSET_Y 800
#define BOSS_DEADZONE_X 5
#define BOSS_DEADZONE_Y 2

struct Boss{
    int x, y;                                    // posição do boss.
    int width, height;                           // largura e altura do boss.
    int dir_x, dir_y;                            // direção do boss.
    int lives;                                   // quantidade de vida.
    int shot_cooldown;                           // cooldown dos tiros.
    int walk, attack1, sleep;                    // auxiliar na hora de desenhar os sprites.
    int anim_frame, anim_counter;                // auxiliar na hora de desenhar os sprites.
    int last_state;                              // 0: idle, 1: walk. 2: sleep. 3: died. 4: attack1. 5: wakeup.
    int damage_cooldown;                         // após tomar dano, piscar. 
};

struct Player;
struct Display;
struct ShotManager;

// inicializa o boss.
void boss_init(struct Boss *boss, struct Display *display);

// atualiza o boss.
void boss_update(struct Boss *boss, struct ShotManager *pistol, struct Player *player, struct Display *display);

// desenha o boss.
void boss_draw(struct Boss *boss, int camera_x);


#endif