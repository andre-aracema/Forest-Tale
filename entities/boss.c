#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "boss.h"
#include "display.h"
#include "shot.h"
#include "collision.h"
#include "player.h"
#include "sprites_boss.h"

void boss_init(struct Boss *boss, struct Display *display){
    boss->x = display->background_game * 0.5;
    boss->y = display->height - BOSS_INITIAL_OFFSET_Y;
    boss->width = BOSS_WIDTH;
    boss->height = BOSS_HEIGHT;
    boss->lives = BOSS_LIVE;
    boss->dir_x = NEUTRO;
    boss->dir_y = NEUTRO;
    boss->walk = 0;
    boss->sleep = 1;
    boss->attack1 = 0;
    boss->anim_frame = 0;
    boss->anim_counter = 0;
    boss->last_state = 0;
    boss->damage_cooldown = 0;
}

void boss_update(struct Boss *boss, struct ShotManager *pistol, struct Player *player, struct Display *display){
    boss->walk = 0;
    boss->attack1 = 0;
    int current_state = 0;
    int type_attack = 0;

    // sprite.
    boss->anim_counter++;
    if(boss->anim_counter >= 8){
        boss->anim_counter = 0;
        boss->anim_frame++;
    }

    // fazer verificação se boss acordou (player fazer 600 pontos).
    if((player->score >= 600) && (boss->sleep)){
        boss->sleep = 0;
        current_state = 5;                            // wakeup.
        return;
    }
    
    if(!boss->sleep){
        // fases do boss.
        if(boss->lives <= BOSS_LIVE * 0.5)
            type_attack = 0;                                 // ataque corpo a corpo.
        else
            type_attack = 1;
                         
        // boss esta vivo.
        if(boss->lives > 0){
            int distance_x = (player->x) - (boss->x + boss->width / 2);
            int distance_y = (player->y + player->height / 2) - (boss->y + boss->height / 2);

            // se jogar estiver na linha de tiro do boss.
            if((abs(distance_x) < display->width / 8) && (type_attack == 1)){
                // 'zona morta'.
                if(abs(distance_x) > BOSS_DEADZONE_X){
                    if(distance_x < 0)
                        boss->dir_x = LEFT;
                    else if(distance_x >= 0)
                        boss->dir_x = RIGHT;

                }

                if(abs(distance_y) > BOSS_DEADZONE_Y){
                    if(distance_y < 0)
                        boss->dir_y = UP;
                    else if(distance_y >= 0)
                        boss->dir_y = DOWN;
                }

                if(boss->shot_cooldown == 0){
                    boss_shot_update(pistol, boss, player);
                    current_state = 4;                 // attack1.
                    boss->attack1 = 1;
                }
            }

            // se jogador estiver na visão do inimigo (jogo inteiro).
            else if(abs(distance_x) < display->background_game){
                if(abs(distance_x) > BOSS_DEADZONE_X){
                    if(distance_x < 0){
                        boss->x -= BOSS_SPEED;
                        boss->dir_x = LEFT;
                    }
                    else if(distance_x >= 0){
                        boss->x += BOSS_SPEED;
                        boss->dir_x = RIGHT;
                    }
                }
                if((abs(distance_y) > BOSS_DEADZONE_Y) && type_attack == 0){
                    if(distance_y < 0){
                        boss->y -= BOSS_SPEED_Y;
                        boss->dir_y = UP;
                    } 
                    else if(distance_y >= 0){
                        boss->y += BOSS_SPEED_Y;
                        boss->dir_y = DOWN;
                    }
                }

                current_state = 1;               // walk.
                boss->walk = 1;
            }
        }
        else if(boss->lives <= 0){
            current_state = 3;                   // died.
        }
        else{
            current_state = 2;                  // sleep.
        }
        
    }

    // garante que o boss não saia do background.
    if(boss->x < 0)
        boss->x = 0;

    if(boss->y < 0)
        boss->y = 0;

    if(boss->x > display->background_game - boss->width)
        boss->x = display->background_game - boss->width;
    
    if(boss->y > display->height - boss->height - 200)
        boss->y = display->height - boss->height - 200;
        
    // diminuindo cooldown de dano.
    if(boss->damage_cooldown > 0)
        boss->damage_cooldown--;

    // zerando index do frame.
    if(current_state != boss->last_state){
        boss->anim_frame = 0;
        boss->anim_counter = 0;
        boss->last_state = current_state;
    }
}

void boss_draw(struct Boss *boss, int camera_x){
    if((boss->anim_frame >= BOSS_DIE) && (boss->lives <=0))
        return;
    
    // sprite.
    int frame = boss->anim_frame;
    ALLEGRO_BITMAP *sprite_draw = NULL;

    if((boss->dir_x == LEFT) || (boss->dir_x == NEUTRO)){
        // atacando.
        if(boss->attack1){
            frame = 5;
            sprite_draw = boss_sprites_l.attack1[frame];
        }
        // morrendo.
        else if(boss->lives <= 0){
            frame %= BOSS_DIE;
            sprite_draw = boss_sprites_l.die[frame];
        }
        // andando.
        else if(boss->walk){
            frame %= BOSS_WALK;
            sprite_draw = boss_sprites_l.walk[frame];
        }
        // dormindo.
        else if(boss->sleep){
            frame %= BOSS_SLEEP;
            sprite_draw = boss_sprites_l.sleep[frame];
        }
        // parado.
        else{
            frame %= BOSS_IDLE;
            sprite_draw = boss_sprites_l.idle[frame];
        }
    }
    else if(boss->dir_x == RIGHT){
        // atacando.
        if(boss->attack1){
            frame = 2;
            sprite_draw = boss_sprites_r.attack1[frame];
        }
        // morrendo.
        else if(boss->lives <= 0){
            frame %= BOSS_DIE;
            sprite_draw = boss_sprites_r.die[frame];
        }
        // andando.
        else if(boss->walk){
            frame %= BOSS_WALK;
            sprite_draw = boss_sprites_r.walk[frame];
        }
        // dormindo.
        else if(boss->sleep){
            frame %= BOSS_SLEEP;
            sprite_draw = boss_sprites_r.sleep[frame];
        }
        // parado.
        else{
            frame %= BOSS_IDLE;
            sprite_draw = boss_sprites_r.idle[frame];
        }
    }

    // efeito de piscar quando toma dano.
    if((boss->damage_cooldown > 0) && (sprite_draw) && (boss->lives >= 0 || boss->anim_frame < BOSS_DIE)){
        al_draw_tinted_scaled_bitmap(
                    sprite_draw,                                   // sprite original.
                    al_map_rgb(255, 0, 0),                         // vermelho.
                    0, 5,                                          // coordenadas (x, y) de início.
                    al_get_bitmap_width(sprite_draw),              // largura original.
                    al_get_bitmap_height(sprite_draw),             // altura original.
                    boss->x - camera_x, boss->y,                   // posição na tela.
                    al_get_bitmap_width(sprite_draw),              // largura.
                    al_get_bitmap_height(sprite_draw),             // altura.
                    0);
    }

    else if((sprite_draw) && (boss->lives >= 0 || boss->anim_frame < BOSS_DIE)){
        al_draw_scaled_bitmap(
                    sprite_draw,                                   // sprite original.
                    0, 5,                                          // coordenadas (x, y) de início.
                    al_get_bitmap_width(sprite_draw),              // largura original.
                    al_get_bitmap_height(sprite_draw),             // altura original.
                    boss->x - camera_x, boss->y,                   // posição na tela.
                    al_get_bitmap_width(sprite_draw),              // largura.
                    al_get_bitmap_height(sprite_draw),             // altura.
                    0); 
    }
}