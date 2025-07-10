#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "system.h"
#include "buttons.h"
#include "shot.h"
#include "boss.h"
#include "display.h"
#include "player.h"
#include "enemy.h"
#include "reset.h"
#include "state.h"
#include "item.h"

enum State state = STATE_MENU;

void  handle_mouse_click(enum State *state, struct ButtonGroup *buttons, struct Display *disp,
                        struct Player **player, struct ShotManager *pistol, struct Item *items,
                        struct Boss *boss, float mx, float my, int *game_running, int *camera_x){
    switch(*state){
        case STATE_MENU:
            // percorre os botões do menu para verificar se algum foi clicado.
            for(int i = 0; i < MENU_BUTTONS; i++){
                if(is_inside_button(buttons->menu[i], mx, my)){
                    if(i == 0)
                        *state = STATE_GAME;
            
                    if(i == 1)
                        *state = STATE_SETTINGS;
                    
                    if(i == 2)
                        *game_running = 1;
                }
            }
            break;

        case STATE_SETTINGS:
            // percorre os botões das configurações para verificar se algum foi clicado.
            for(int i = 0; i < SETTINGS_BUTTONS; i++){
               if(is_inside_button(buttons->settings[i], mx, my)){
                    if (i == 0)
                        display_reset(disp, buttons, player, pistol, items, boss, 0, camera_x);
                    
                    if (i == 1)
                        display_reset(disp, buttons, player, pistol, items, boss, 1, camera_x);
                    
                    if (i == 2)
                        *state = STATE_MENU;
                }
            }
            break;

        case STATE_PAUSE:
            // percorre os botões do pause para verificar se algum foi clicado.
            for(int i = 0; i < PAUSE_BUTTONS; i++){
                if(is_inside_button(buttons->pause[i], mx, my)){
                    if(i == 0)
                        *state = STATE_GAME;
            
                    if(i == 1)
                        *game_running = 1;
                }
            }
            break;

        case STATE_GAMEOVER:
            // percorre os botões do game over para verificar se algum foi clicado.
            for(int i = 0; i < GAMEOVER_BUTTONS; i++){
                if(is_inside_button(buttons->gameover[i], mx, my)){
                    if(i == 0)
                        *state = STATE_GAME;
            
                    if(i == 1)
                        *state = STATE_MENU;
                }
            }
            break;

        case STATE_VICTORY:
            // percorre os botões do victory para verificar se algum foi clicado.
            for(int i = 0; i < VICTORY_BUTTONS; i++){
                if(is_inside_button(buttons->victory[i], mx, my)){
                    if(i == 0)
                        *state = STATE_GAME;
            
                    if(i == 1)
                        *state = STATE_MENU;
                }
            }
            break;

        default:
            break;
    }
}

void handle_timer_event(enum State *state, struct Player **player, struct Display *display,
                        struct ShotManager *pistol, struct Boss *boss, struct Item *items,
                        float *time_player_death, float *time_boss_death, int *camera_x, unsigned char *key){

    switch(*state){
        case STATE_GAME:
            if(key[ALLEGRO_KEY_ESCAPE]){
                *state = STATE_PAUSE;
                (*player)->shot_cooldown = 15;
                break;
            }
                
            player_update(*player, display, pistol, boss);
            enemies_update(pistol, *player, display);
            boss_update(boss, pistol, *player, display);
            item_update(items, *player);
                
            enemy_shots_update(pistol, display, *player, *camera_x);
            if(!boss->sleep)
                boss_shots_update(pistol, display, *player, boss, *camera_x);
            player_shots_update(pistol, display, *player, boss, *camera_x);
                    
            // lógica do game over.
            if((*player)->lives <= 0){
                if(*time_player_death < 0)
                    *time_player_death = al_get_time();                         // momento da morte.
                else if(al_get_time() - *time_player_death >= 2){
                    *state = STATE_GAMEOVER;
                    game_reset_init(player, pistol, display, items, boss, camera_x);    
                    *time_player_death = PLAYER_ALIVE;
                }
            }
            // lógica do victory.
            if(boss->lives <= 0){
                if(*time_boss_death < 0)
                    *time_boss_death = al_get_time();
                else if(al_get_time() - *time_boss_death >= 3){
                    *state = STATE_VICTORY;
                    game_reset_init(player, pistol, display, items, boss, camera_x);  
                    *time_boss_death = BOSS_ALIVE;
                }  
            }
            break;

        default:
            break;
    }         
}
