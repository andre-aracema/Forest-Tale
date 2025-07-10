#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "display.h"
#include "shot.h"
#include "collision.h"
#include "player.h"
#include "enemy.h"
#include "sprites_enemy.h"

struct Enemy enemies[ENEMY_MAX];

void enemies_init(struct Display *display){
    // tamanho do inimigo.
    int height = display->height * ENEMY_HEIGHT_PERC;
    int width = display->width * ENEMY_WIDTH_PERC;

    for(int i = 0; i < ENEMY_MAX; i++){
        enemies[i].x = display->width + i * 700;
        enemies[i].y = display->height * FLOOR_PLAYER - height;
        enemies[i].width = width;
        enemies[i].height = height;
        enemies[i].dir = NEUTRO;
        enemies[i].lives = ENEMY_LIVES;
        enemies[i].shot_cooldown = 32;
        enemies[i].walk = 0;
        enemies[i].attack = 0;
        enemies[i].anim_frame = 0;
        enemies[i].anim_counter = 0;
        enemies[i].last_state = 0;
        enemies[i].damage_cooldown = 0;
    }
}

void enemies_update(struct ShotManager *pistol, struct Player *player, struct Display *display){
    for(int i = 0; i < ENEMY_MAX; i++){
        enemies[i].walk = 0;
        enemies[i].attack = 0;
        int current_state = 0;

        // sprite.
        enemies[i].anim_counter++;
        if(enemies[i].anim_counter >= 8){
            enemies[i].anim_counter = 0;
            enemies[i].anim_frame++;
        }

        if(enemies[i].lives > 0){
            int distance = (player->x + player->width / 2) - (enemies[i].x + enemies[i].width / 2);

            // se jogador estiver na linha de tiro do inimigo.
            if(abs(distance) < display->width / 3){
                if(distance < 0)
                    enemies[i].dir = LEFT;
                
                else if(distance > 0)
                    enemies[i].dir = RIGHT;
                
                enemy_shot_update(pistol, &enemies[i]);

                current_state = 4;                        // attack.
                enemies[i].attack = 1;
            }
            // se jogador estiver na visão do inimigo.
            else if(abs(distance) < display->width / 2){
                enemies[i].shot_cooldown = 32;

                if(distance < 0){
                    enemies[i].x -= ENEMY_SPEED;
                    enemies[i].dir = LEFT;
                }
                else if(distance > 0){
                    enemies[i].x += ENEMY_SPEED;
                    enemies[i].dir = RIGHT;
                }

                current_state = 1;                       // walk.
                enemies[i].walk = 1;
            }
        }
        else{
            current_state = 3;                           // dead.
        }

        // garante que inimigo não saia do background.
        if(enemies[i].x < 0)
            enemies[i].x = 0;

        if(enemies[i].x > display->background_game - enemies[i].width)
            enemies[i].x = display->background_game - enemies[i].width;
        
        // diminuindo cooldown de dano.
        if(enemies[i].damage_cooldown > 0)
            enemies[i].damage_cooldown--;

        // zerando index do frame.
        if(current_state != enemies[i].last_state){
            enemies[i].anim_frame = 0;
            enemies[i].anim_counter = 0;
            enemies[i].last_state = current_state;
        }
    }
}

void enemies_draw(int camera_x){
    for(int i = 0; i < ENEMY_MAX; i++){
        if((enemies[i].anim_frame >= ENEMY_DIED) && (enemies[i].lives <= 0))
            continue;

        // sprite.
        int frame = enemies[i].anim_frame;
        ALLEGRO_BITMAP *sprite_draw = NULL;

        if(enemies[i].dir == LEFT){
            // morrendo.
            if(enemies[i].lives <= 0){
                frame %= ENEMY_DIED;
                sprite_draw = enemy_sprites_l.died[frame];
            }
            // andando.
            else if(enemies[i].walk){
                frame %= ENEMY_WALK;
                sprite_draw = enemy_sprites_l.walk[frame];
            }
            // atacando.
            else if(enemies[i].attack){
                frame %= ENEMY_ATTACK;
                sprite_draw = enemy_sprites_l.attack[frame];
            }
            // parado.
            else{
                frame %= ENEMY_IDLE;
                sprite_draw = enemy_sprites_l.idle[frame];
            }
        }
        else if((enemies[i].dir == RIGHT) || (enemies[i].dir == NEUTRO)){
            // morrendo.
            if(enemies[i].lives <= 0){
                frame %= ENEMY_DIED;
                sprite_draw = enemy_sprites_r.died[frame];
            }
            // andando.
            else if(enemies[i].walk){
                frame %= ENEMY_WALK;
                sprite_draw = enemy_sprites_r.walk[frame];
            }
            // atacando.
            else if(enemies[i].attack){
                frame %= ENEMY_ATTACK;
                sprite_draw = enemy_sprites_r.attack[frame];
            }
            // parado.
            else{
                frame %= ENEMY_IDLE;
                sprite_draw = enemy_sprites_r.idle[frame];
            }
        }

        // efeito de piscar quando toma dano.
        if((enemies[i].damage_cooldown > 0) && (sprite_draw) && (enemies[i].lives >= 0 || enemies[i].anim_frame < ENEMY_DIED)){
            al_draw_tinted_scaled_bitmap(
                    sprite_draw,                                   // sprite original.
                    al_map_rgb(255, 0, 0),                         // vermelho.
                    0, 5,                                          // coordenadas (x, y) de início.
                    al_get_bitmap_width(sprite_draw),              // largura original.
                    al_get_bitmap_height(sprite_draw),             // altura original.
                    enemies[i].x - camera_x, enemies[i].y,         // posição na tela.
                    al_get_bitmap_width(sprite_draw),              // largura.
                    al_get_bitmap_height(sprite_draw),             // altura.
                    0);
        }

        else if((sprite_draw) && (enemies[i].lives >= 0 || enemies[i].anim_frame < ENEMY_DIED)){
            al_draw_scaled_bitmap(
                    sprite_draw,                                   // sprite original.
                    0, 5,                                          // coordenadas (x, y) de início.
                    al_get_bitmap_width(sprite_draw),              // largura original.
                    al_get_bitmap_height(sprite_draw),             // altura original.
                    enemies[i].x - camera_x, enemies[i].y,         // posição na tela.
                    al_get_bitmap_width(sprite_draw),              // largura.
                    al_get_bitmap_height(sprite_draw),             // altura.
                    0); 
        }
    }
}

struct Enemy *enemies_get(){
    return enemies;
}