#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_ALIVE -1
#define PLAYER_LIVES 6
#define PLAYER_STEP 15
#define PLAYER_HEIGHT_PERC 0.1185
#define PLAYER_WIDTH_PERC 0.055
#define FLOOR_PLAYER 0.95

#define PLAYER_RELOAD_SHOT 10

#define LEFT -1
#define RIGHT 1
#define UP -1
#define DOWN 1
#define NEUTRO 0

// estrutura do jogador (player).
struct Player{ 
    int x, y;                               // posição do jogador.
    int width, height;                      // largura e altura do jogador, respectivamente.
    int lives;                              // vidas do player.
    int speed_y;                            // velocidade vertical (salto).
    int damage_cooldown;                    // após tomar dano, imunidade.
    int last_dx, last_dy;                   // auxiliar na hora de atirar. Direção atual do jogador.
    int attack;                             // auxiliar na hora de atirar. Esta atirando.
    int walk, crouched;                     // auxiliar na hora de desenhar os sprites.
    int sprite_dir;                         // auxiliar na hora de desenhar os sprites.
    int anim_frame, anim_counter;           // auxiliar na hora de desenhar os sprites.
    int last_state;                         // 0: idle, 1: walk. 2: jump, 3: crouched. 4: died. 5: attack.
    int ground;                             // chão do player.
    int offset_crouched;                    // auxiliar no hitbox.
    int ammunition;                         // quantidade de munição que o personagem possui.
    int reloading;                          // se esta recarregando.
    int shot_cooldown;                      // tempo entre os tiros.
    int score;                              // pontuação.
    int double_jump;                        // pulo duplo.
    int jump_count, jump_pressed;           // auxiliares para pulo duplo.
};

struct ShotManager;
struct Display;
struct Item;
struct Boss;

// cria e inicializa o jogador.
struct Player *player_create(struct Display *display);

// libera memória alocada para o jogador.
void player_destroy(struct Player *player);

// atualiza a posição do jogador.
void player_update(struct Player *player, struct Display *display, struct ShotManager *pistol, struct Boss *boss);

// desenha o jagador na tela.
void player_draw(struct Player *player, struct Display *display, int camera_x);

// desenha as vidas do jogador na tela.
void player_status_draw(struct Player *player, struct Item *items, float time);

#endif