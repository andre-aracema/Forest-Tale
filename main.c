#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Allegro
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

// Project
#include "display.h"
#include "buttons.h"
#include "camera.h"
#include "reset.h"
#include "collision.h"
#include "state.h"
#include "system.h"
#include "enemy.h"
#include "player.h"
#include "boss.h"
#include "shot.h"
#include "sprites_player.h"
#include "sprites_bullet.h"
#include "sprites_enemy.h"
#include "sprites_enemy_bullet.h"
#include "sprites_boss_bullet.h"
#include "sprites_boss.h"
#include "background.h"
#include "item.h"
#include "render.h"

#define FPS 30

int main(){
    init_allegro();

    ALLEGRO_TIMER *timer = al_create_timer(1.0/FPS);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_FONT *font = al_load_ttf_font("assets/fonts/PressStart2P-Regular.ttf", 12, 0);
    must_init(font, "font PressStart2P");

    ALLEGRO_BITMAP *menu = load_bitmap("assets/backgrounds/menu.png", "menu");
    ALLEGRO_BITMAP *settings = load_bitmap("assets/backgrounds/settings.png", "settings");
    ALLEGRO_BITMAP *pause = load_bitmap("assets/backgrounds/pause.png", "pause");
    ALLEGRO_BITMAP *background = load_bitmap("assets/backgrounds/game.png", "background");
    ALLEGRO_BITMAP *gameover = load_bitmap("assets/backgrounds/gameover.png", "gameover");
    ALLEGRO_BITMAP *victory = load_bitmap("assets/backgrounds/victory.png", "victory");

    struct Display display;
    display_init(&display, 1);

    al_register_event_source(queue, al_get_display_event_source(display.display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    // inicializando botões.
    struct ButtonGroup buttons;
    struct Button menu_buttons[MENU_BUTTONS];
    struct Button setting_buttons[SETTINGS_BUTTONS];
    struct Button pause_buttons[PAUSE_BUTTONS];
    struct Button gameover_buttons[GAMEOVER_BUTTONS];
    struct Button victory_buttons[VICTORY_BUTTONS];

    buttons.menu = menu_buttons;
    buttons_init(buttons.menu, display.width, display.height, MENU_BUTTONS, 0);
    buttons.settings = setting_buttons;
    buttons_init(buttons.settings, display.width, display.height, SETTINGS_BUTTONS, 0);
    buttons.pause = pause_buttons;
    buttons_init(buttons.pause, display.width, display.height, PAUSE_BUTTONS, 1);
    buttons.gameover = gameover_buttons;
    buttons_init(gameover_buttons,display.width, display.height, GAMEOVER_BUTTONS, 1);
    buttons.victory = victory_buttons;
    buttons_init(victory_buttons, display.width, display.height, VICTORY_BUTTONS, 1);

    // inicializando player.
    struct Player *player = player_create(&display);
    if(!player){
        return 1;
    }

    // disparos.
    struct ShotManager pistol;

    // boss.
    struct Boss boss;

    // itens (vida, bota de salto duplo).
    struct Item items[ITEMS_TOTAL];

    // posição da câmera (movimentação relativa).
    int camera_x = 0;

    // tempo após a morte do player.
    float time_player_death = PLAYER_ALIVE;

    // tempo após a morte do boss.
    float time_boss_death = BOSS_ALIVE;            

    // iniciando.
    enemies_init(&display);
    boss_init(&boss, &display);
    shots_init(&pistol, player, &boss);
    item_init(items, &display);
    keyboard_mouse_init();
    player_sprites_init();
    bullet_sprites_init();
    enemy_sprites_init();
    boss_sprites_init();
    bullet_enemy_sprites_init();
    bullet_boss_sprites_init();

    int game_running = 0;
    int redraw = 1;
    enum State state = STATE_MENU;

    ALLEGRO_EVENT event;
    al_start_timer(timer);

    while(!game_running){
        al_wait_for_event(queue, &event);
        switch(event.type){
            case ALLEGRO_EVENT_TIMER:
                handle_timer_event(&state, &player, &display, &pistol, &boss, items, &time_player_death, &time_boss_death, &camera_x, key);
                redraw = 1;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                handle_mouse_click(&state, &buttons, &display, &player, &pistol, items, &boss, event.mouse.x, event.mouse.y, &game_running, &camera_x);
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                game_running = 1;
                break;
        }

        keyboard_mouse_update(&event);

        if(redraw && al_is_event_queue_empty(queue)){
            al_clear_to_color(al_map_rgb(0, 0, 0));
            switch(state){
                case STATE_MENU: 
                    render_menu(menu, &display); 
                    break;
                case STATE_SETTINGS: 
                    render_settings(settings, &display); 
                    break;
                case STATE_PAUSE: 
                    render_pause(pause, &display); 
                    break;
                case STATE_GAMEOVER: 
                    render_gameover(gameover, &display); 
                    break;              
                case STATE_VICTORY: 
                    render_victory(victory, &display); 
                    break;
                case STATE_GAME: 
                    render_game(background, font, &display, player, items, &pistol, &boss, &camera_x, al_get_time()); 
                    break;
            }

            al_flip_display();
            redraw = 0;
        }
    }

    cleanup(menu, background, settings, gameover, pause, victory, font, timer, queue, player, &display, items);
    return 0;
}