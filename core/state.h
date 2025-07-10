#ifndef STATE_H
#define STATE_H

// estados do jogo.
enum State{
    STATE_MENU,              // estado do menu principal.
    STATE_SETTINGS,          // estado das configurações.
    STATE_PAUSE,             // estado de pause.
    STATE_GAME,              // estado do jogo.
    STATE_GAMEOVER,          // estado de game over.
    STATE_VICTORY            // acabou o jogo.
};

struct ButtonGroup;
struct Display;
struct Player;
struct ShotManager;
struct Item;

// processa o click do mouse nos diferentes estados, exeto o estado de jogo.
void  handle_mouse_click(enum State *state, struct ButtonGroup *buttons, struct Display *disp,
                        struct Player **player, struct ShotManager *pistol, struct Item *items, 
                        struct Boss *boss, float mx, float my, int *game_running, int *camera_x);

// lida com os eventos do tipo 'timer' nos diferentes estado.
void handle_timer_event(enum State *state, struct Player **player, struct Display *display,
                        struct ShotManager *pistol, struct Boss *boss, struct Item *items,
                        float *time_player_death, float *time_boss_death, int *camera_x, unsigned char *key);


#endif