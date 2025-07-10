#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "item.h"
#include "system.h"
#include "sprites_player.h"
#include "player.h"
#include "display.h"
#include "collision.h"

void item_init(struct Item *item, struct Display *disp){
    // filtro para malhorar qualidade do sprite.
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    // inicializando item de vida.
    for(int i = 0; i < ITEMS_LIVE_MAX; i++){
        item[i].sprite = al_load_bitmap("assets/sprites/items/item_live.png");
        item[i].x = disp->background_game / 2 + i * disp->width;
        item[i].y = disp->height - 270 - i * 150;
        item[i].active = 1;
        item[i].type = ITEM_LIFE;
    }

    // inicializando item de bota.
    int bota_index = ITEMS_LIVE_MAX;          // após os itens de vida.
    item[bota_index].sprite = al_load_bitmap("assets/sprites/items/boot.png");
    item[bota_index].x = disp->width * 1.5;
    item[bota_index].y = disp->height - 270;
    item[bota_index].active = 1;
    item[bota_index].type = ITEM_BOOT;
}

void item_update(struct Item *item, struct Player *player){
    for(int i = 0; i < ITEMS_TOTAL; i++){
        if(!item[i].active)
            continue;;

        // calculando colisão diretamente.
        int ax1 = item[i].x; 
        int ay1 = item[i].y;
        int ax2 = ax1 + al_get_bitmap_width(item[i].sprite);
        int ay2 = ay1 + al_get_bitmap_height(item[i].sprite);

        // bordas do jogador
        int bx1 = player->x + 10;
        int by1 = player->y + 15 + player->offset_crouched;
        int bx2 = player->x + player->width;
        int by2 = player->y + player->height;

        if(collide(ax1, ay1, ax2, ay2, bx1, by1, bx2, by2)){
            if(item[i].type == ITEM_LIFE){
                if(player->lives < 10)
                    player->lives += 2;
            }
            else if(item[i].type == ITEM_BOOT)
                player->double_jump = 1;

            item[i].active = 0;
        }
    }
}

void item_draw(struct Item *item, int camera_x, float time){
    for(int i = 0; i < ITEMS_TOTAL; i++){
        if((item[i].active) && (item[i].sprite)){
            // efeito de flutuar utilizando seno.
            float offset = 3 * sin(time * 10 + i);

            al_draw_bitmap(item[i].sprite, item[i].x - camera_x, item[i].y + offset, 0);
        }
    }
}

void item_destroy(struct Item *item){
    for(int i = 0; i < ITEMS_TOTAL; i++){
        if(item[i].sprite)
            al_destroy_bitmap(item[i].sprite);
    }
}