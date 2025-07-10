#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_LIVES 6
#define ENEMY_MAX 6
#define ENEMY_SPEED 7
#define FLOOR_ENEMY 0.95

#define ENEMY_HEIGHT_PERC 0.1185
#define ENEMY_WIDTH_PERC 0.055

struct Enemy{
    int x, y;                           // posição do inimigo.
    int dir;                            // direção do inimigo.
    int width, height;                  // largura e altura do inimigo.
    int lives;                          // quantidade de vida.
    int shot_cooldown;                  // cooldown dos tiros.
    int walk, attack;                   // auxiliar na hora de desenhar os sprites.
    int anim_frame, anim_counter;       // auxiliar na hora de desenhar os sprites.
    int last_state;                     // 0: idle, 1: walk. 3: died. 4: attack.
    int damage_cooldown;                // após tomar dano, piscar. 
};

struct Player;
struct Display;
struct ShotManager;

// inicializa os inimigos.
void enemies_init(struct Display *display);

// atualiza os inimigos.
void enemies_update(struct ShotManager *pistol, struct Player *player, struct Display *display);

// desenha os inimigos na tela.
void enemies_draw(int camera_x);

// ponteiro para lista de inimigos.
struct Enemy *enemies_get();

#endif
