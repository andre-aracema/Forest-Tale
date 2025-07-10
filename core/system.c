#include <stdio.h>
#include <stdbool.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "sprites_boss.h"
#include "sprites_enemy.h"
#include "sprites_player.h"
#include "sprites_bullet.h"
#include "sprites_boss_bullet.h"
#include "sprites_enemy_bullet.h"
#include "player.h"
#include "display.h"
#include "item.h"
#include "system.h"

unsigned char key[ALLEGRO_KEY_MAX];         // vetor que guarda o estado de todas as teclas.
unsigned char mouse[MOUSE_MAX];             // vetor que guarda o estado dos botões do mouse.

void keyboard_mouse_init(){
    memset(key, 0, sizeof(key));
    memset(mouse, 0, sizeof(mouse));
}

void keyboard_mouse_update(ALLEGRO_EVENT* event){
    switch(event->type){
        case ALLEGRO_EVENT_TIMER:
            for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                key[i] &= ~KEY_SEEN;                             // limpa o bit KEY_SEEN, mantendo o KEY_DOWN se ainda estiver pressionado.
            for(int i = 0; i < MOUSE_MAX; i++)
                mouse[i] &= ~KEY_SEEN;                           // mesmo para os botões do mouse.
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            key[event->keyboard.keycode] = KEY_SEEN | KEY_DOWN;  // marca a tecla como nova e pressionada (00000011).
            break;
        case ALLEGRO_EVENT_KEY_UP:
            key[event->keyboard.keycode] &= ~KEY_DOWN;           // remove apenas o bit KEY_DOWN (pressionada).
            break;
        
        // o mesmo para o mouse.
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            mouse[event->mouse.button] = KEY_SEEN | KEY_DOWN;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            mouse[event->mouse.button] &= ~KEY_DOWN;
            break;
    }
}

//-----------------------------------------------------------------------------------//

void must_init(bool test, const char *definition){
    if(!test){
        printf("Não foi possível inicializar %s\n", definition);
        exit(1);
    }
}

void init_allegro(){
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
}

//------------------------------------------------------------------------------------//

ALLEGRO_BITMAP *load_bitmap(const char *path, const char *debug){
    ALLEGRO_BITMAP *bitmap = al_load_bitmap(path);
    must_init(bitmap, debug);
    return bitmap;
}

void cleanup(ALLEGRO_BITMAP *menu, ALLEGRO_BITMAP *background, ALLEGRO_BITMAP *settings, ALLEGRO_BITMAP *gameover,
            ALLEGRO_BITMAP *pause, ALLEGRO_BITMAP *victory, ALLEGRO_FONT *font, ALLEGRO_TIMER *timer, ALLEGRO_EVENT_QUEUE *queue,
            struct Player *player, struct Display *display, struct Item *items){

    al_destroy_bitmap(menu);
    al_destroy_bitmap(background);
    al_destroy_bitmap(settings);
    al_destroy_bitmap(gameover);
    al_destroy_bitmap(pause);
    al_destroy_bitmap(victory);

    item_destroy(items);
    player_sprites_destroy();
    bullet_sprites_destroy();
    enemy_sprites_destroy();
    boss_sprites_destroy();
    bullet_enemy_sprites_destroy();
    bullet_boss_sprites_destroy();
    
    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    player_destroy(player);
    display_destroy(display);
}