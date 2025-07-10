#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "sprites_bullet.h"
#include "sprites_enemy_bullet.h"
#include "collision.h"
#include "display.h"
#include "player.h"
#include "enemy.h"
#include "boss.h"
#include "shot.h"
#include "sprites_boss_bullet.h"

void shots_init(struct ShotManager *pistol, struct Player *player, struct Boss *boss){
    struct Enemy *enemies = enemies_get();
    
    for(int i = 0; i < SHOTS_MAX; i++){
        pistol->shots[i].used = 0;
        pistol->shots_enemy[i].used = 0;
    }

    for(int i = 0; i < ENEMY_MAX; i++)
        enemies[i].shot_cooldown = 60;

    boss->shot_cooldown = 60;
    player->shot_cooldown = 15;              // atraso inicial de 1/2 segundo (15 frames).
}

//--------------------------------------PLAYER-------------------------------------------//

void player_shot_add(struct ShotManager *pistol, int x, int y, int dx, int dy, int width, int height){
    for(int i = 0; i < SHOTS_MAX; i++){
        // procura por tiros não utilizados.
        if(!pistol->shots[i].used){
            pistol->shots[i].x = x;
            pistol->shots[i].y = y;
            pistol->shots[i].dx = dx;
            pistol->shots[i].dy = dy;
            pistol->shots[i].width = width;
            pistol->shots[i].height = height;
            pistol->shots[i].col_w = 20;
            pistol->shots[i].col_h = 20;
            pistol->shots[i].used = 1;
            pistol->shots[i].anim_frame = 0;
            pistol->shots[i].anim_counter = 0;
            pistol->shots[i].offset_up = 0;
            break;
        }
    }
}

void player_shots_update(struct ShotManager *pistol, struct Display *disp, struct Player *player, struct Boss *boss, int camera_x){
    for(int i = 0; i < SHOTS_MAX; i++){
        // procura por tiros ativos.
        if(!pistol->shots[i].used)
            continue;
        
        pistol->shots[i].x += pistol->shots[i].dx;
        pistol->shots[i].y += pistol->shots[i].dy;

        // sprite.
        pistol->shots[i].anim_counter++;
        if(pistol->shots[i].anim_counter >= 8){
            pistol->shots[i].anim_counter = 0;
            pistol->shots[i].anim_frame++;
        }

        // se tiro sair da tela.
        if(pistol->shots[i].x < camera_x || pistol->shots[i].x > camera_x + disp->width || 
            pistol->shots[i].y < 0 || pistol->shots[i].y > disp->height){
            pistol->shots[i].used = 0;
            continue;
        }

        // verificação de colisão com inimigo.
        collide_shot_enemy(pistol, player, i);
        collide_shot_boss(pistol, player, boss, i);
    }

    // tempo de cooldown.
    if(player->shot_cooldown > 0)
        player->shot_cooldown--;
}

void player_shot_update(struct ShotManager *pistol, struct Player *player){
    // verifica cooldown.
    if(player->shot_cooldown == 0){
        int x = player->x;
        int y = player->y + (player->height / 2) - (BULLET_HS / 2);
        int width = BULLET_WS;
        int height = BULLET_HS;

        // define direção.

        // atira para cima.
        if(player->last_dy == UP){
            width = BULLET_UP_WS;
            height = BULLET_UP_HS;
            y = player->y - (height / 2);
            x = player->x + (player->width / 2) - (width / 2);
        }
        // atira para a esquerda.
        if(player->last_dx == LEFT)
            x = player->x - width + 5;
        
        // atira para direita.
        if(player->last_dx == RIGHT)
            x =  player->x + player->width - width + 10;

        if(player->crouched)
            y = player->y + player->height * 0.6;
        
        
        // garantindo que atirou.
        if(player->last_dx != NEUTRO || player->last_dy != NEUTRO){
            player_shot_add(pistol, x, y, player->last_dx * SHOT_PLAYER_SPEED, player->last_dy * SHOT_PLAYER_SPEED, width, height);
            player->shot_cooldown = SHOT_PLAYER_DELAY;
        }
    }
}

void player_shots_draw(struct ShotManager *pistol, int camera_x){
    for(int i = 0; i < SHOTS_MAX; i++){
        // procura por tiros ativos.
        if(!pistol->shots[i].used)
            continue;
        
        pistol->shots[i].offset_up = 0;

        // sprite.
        int frame = pistol->shots[i].anim_frame;
        ALLEGRO_BITMAP *sprite_draw = NULL;

        // direita.
        if(pistol->shots[i].dx > 0){
            frame %= BULLET_ATTACK;
            sprite_draw = bullet_sprites_r.attack[frame];
        }
        // esquerda.
        else if(pistol->shots[i].dx < 0){
            frame %= BULLET_ATTACK;
            sprite_draw = bullet_sprites_l.attack[frame];
        }
        // cima.
        else if(pistol->shots[i].dy < 0){
            pistol->shots[i].offset_up = 10;
            frame %= BULLET_ATTACK_UP;
            sprite_draw = bullet_sprites_u.attack[frame];
        }

        if(sprite_draw){
            al_draw_scaled_bitmap(
                    sprite_draw,                                                  // sprite original.
                    0, 0,                                                         // coordenadas (x, y) de início.
                    al_get_bitmap_width(sprite_draw),                             // largura original.
                    al_get_bitmap_height(sprite_draw),                            // altura original.
                    pistol->shots[i].x - camera_x, pistol->shots[i].y,            // posição na tela.
                    al_get_bitmap_width(sprite_draw) * 1.2,                       // largura.
                    al_get_bitmap_height(sprite_draw) * 1.2,                      // altura.
                    0);
        }
    }
}

//-----------------------------------------------ENEMY-------------------------------------------------//

void enemy_shot_add(struct ShotManager *pistol, int x, int y, int dx, int dy, int width, int height){
    for(int i = 0; i < SHOTS_MAX; i++){
        // procura por tiros não utilizados.
        if(!pistol->shots_enemy[i].used){
            pistol->shots_enemy[i].x = x;
            pistol->shots_enemy[i].y = y;
            pistol->shots_enemy[i].dx = dx;
            pistol->shots_enemy[i].dy = dy;
            pistol->shots_enemy[i].width = width;
            pistol->shots_enemy[i].height = height;
            pistol->shots_enemy[i].col_w = 20;
            pistol->shots_enemy[i].col_h = 20;
            pistol->shots_enemy[i].used = 1;
            pistol->shots_enemy[i].anim_frame = 0;
            pistol->shots_enemy[i].anim_counter = 0;
            pistol->shots_enemy[i].offset_up = 0;
            break;
        }
    }
}

void enemy_shots_update(struct ShotManager *pistol, struct Display *disp, struct Player *player, int camera_x){
    for(int i = 0; i < SHOTS_MAX; i++){
        // procura por tiros ativos.
        if(!pistol->shots_enemy[i].used)
            continue;
        
        // sprite.
        pistol->shots_enemy[i].anim_counter++;
        if(pistol->shots_enemy[i].anim_counter >= 8){
            pistol->shots_enemy[i].anim_counter = 0;
            pistol->shots_enemy[i].anim_frame++;
        }
        
        pistol->shots_enemy[i].x += pistol->shots_enemy[i].dx;
        pistol->shots_enemy[i].y += pistol->shots_enemy[i].dy;

        // se tiro sair da tela.
        if(pistol->shots_enemy[i].x < camera_x || pistol->shots_enemy[i].x > camera_x + disp->width || 
            pistol->shots_enemy[i].y < 0 || pistol->shots_enemy[i].y > disp->height){
            pistol->shots_enemy[i].used = 0;
            continue;
        }

        // verificação de colisão com player.
        collide_enemy_shot_player(pistol, player, i);
    }
}

void enemy_shot_update(struct ShotManager *pistol, struct Enemy *enemy){
    if(enemy->shot_cooldown == 0){
        int x = enemy->x;
        int y = enemy->y + enemy->height / 2;

        if(enemy->dir == RIGHT)
            x = enemy->x + enemy->width;

        // garantindo que atirou.
        if(enemy->dir != NEUTRO){
            enemy_shot_add(pistol, x, y, enemy->dir * SHOT_ENEMY_SPEED, 0, 50, 50);
            enemy->shot_cooldown = SHOT_ENEMY_DELAY;
        }
    }
    else{
        enemy->shot_cooldown--;
    }
}

void enemy_shots_draw(struct ShotManager *pistol, int camera_x){
    for(int i = 0; i < SHOTS_MAX; i++){
        // procura por tiros ativos.
        if(!pistol->shots_enemy[i].used)
            continue;
        
        pistol->shots_enemy[i].offset_up = 0;

        // sprite.
        int frame = pistol->shots_enemy[i].anim_frame;
        ALLEGRO_BITMAP *sprite_draw = NULL;

        // direita.
        if(pistol->shots_enemy[i].dx > 0){
            frame %= BULLET_ENEMY_ATTACK;
            sprite_draw = bullet_enemy_sprites_r.attack[frame];
        }
        // esquerda.
        else if(pistol->shots_enemy[i].dx < 0){
            frame %= BULLET_ENEMY_ATTACK;
            sprite_draw = bullet_enemy_sprites_l.attack[frame];
        }

        if(sprite_draw){
            al_draw_scaled_bitmap(
                    sprite_draw,                                                          // sprite original.
                    0, 0,                                                                 // coordenadas (x, y) de início.
                    al_get_bitmap_width(sprite_draw),                                     // largura original.
                    al_get_bitmap_height(sprite_draw),                                    // altura original.
                    pistol->shots_enemy[i].x - camera_x, pistol->shots_enemy[i].y,        // posição na tela.
                    al_get_bitmap_width(sprite_draw) * 1.2,                               // largura.
                    al_get_bitmap_height(sprite_draw) * 1.2,                              // altura.
                    0);
        }
    }
}


//------------------------------------------------------BOSS--------------------------------------------------------//

void boss_shot_add(struct ShotManager *pistol, int x, int y, int dx, int dy, int width, int height){
    for(int i = 0; i < SHOTS_MAX; i++){
        // procura por tiros não utilizados.
        if(!pistol->shots_boss[i].used){
            pistol->shots_boss[i].x = x;
            pistol->shots_boss[i].y = y;
            pistol->shots_boss[i].dx = dx;
            pistol->shots_boss[i].dy = dy;
            pistol->shots_boss[i].width = width;
            pistol->shots_boss[i].height = height;
            pistol->shots_boss[i].col_w = 20;
            pistol->shots_boss[i].col_h = 20;
            pistol->shots_boss[i].used = 1;
            pistol->shots_boss[i].anim_frame = 0;
            pistol->shots_boss[i].anim_counter = 0;
            pistol->shots_boss[i].offset_up = 0;
            break;
        }
    }
}

void boss_shots_update(struct ShotManager *pistol, struct Display *disp, struct Player *player, struct Boss *boss, int camera_x){
    for(int i = 0; i < SHOTS_MAX; i++){
        // procura por tiros ativos.
        if(!pistol->shots_boss[i].used)
            continue;
        
        // sprite.
        pistol->shots_boss[i].anim_counter++;
        if(pistol->shots_boss[i].anim_counter >= 8){
            pistol->shots_boss[i].anim_counter = 0;
            pistol->shots_boss[i].anim_frame++;
        }
        
        pistol->shots_boss[i].x += pistol->shots_boss[i].dx;
        pistol->shots_boss[i].y += pistol->shots_boss[i].dy;

        // se tiro sair da tela.
        if(pistol->shots_boss[i].x < camera_x || pistol->shots_boss[i].x > camera_x + disp->width || 
            pistol->shots_boss[i].y < 0 || pistol->shots_boss[i].y > disp->height){
            pistol->shots_boss[i].used = 0;
            continue;
        }

        // verificação de colisão com player.
        collide_boss_shot_player(pistol, player, i);
    }

    if(boss->shot_cooldown > 0)
        boss->shot_cooldown--;
}


void boss_shot_update(struct ShotManager *pistol, struct Boss *boss, struct Player *player){
    // iremos utilizar teorema de pitagoras para calcular a direção do tiro.
    if(boss->shot_cooldown == 0){
        int x = boss->x + boss->width / 2;
        int y = boss->y + boss->height / 2;

        // diferença entre o boss e o player.
        float dx = (player->x + player->width / 2) - x;
        float dy = (player->y + player->height / 2) - y;
    
        // comprimento do vetor - formula de Pitágoras.
        float magnitude = sqrtf(dx * dx + dy * dy);
        
        // evitar divisão por zero.
        if(magnitude == 0)
            magnitude = 1;

        // vetor unitário.
        float dir_x = dx / magnitude;
        float dir_y = dy / magnitude;

        boss_shot_add(pistol, x, y, dir_x * SHOT_BOSS_SPEED, dir_y * SHOT_BOSS_SPEED, BULLET_WS, BULLET_HS);
        boss->shot_cooldown = SHOT_BOSS_DELAY;
    }
}

void boss_shots_draw(struct ShotManager *pistol, int camera_x){
    for(int i = 0; i < SHOTS_MAX; i++){
        // procura por tiros ativos.
        if(!pistol->shots_boss[i].used)
            continue;

        // sprite.
        int frame = pistol->shots_boss[i].anim_frame;
        ALLEGRO_BITMAP *sprite_draw = NULL;

        if(pistol->shots_boss[i].dx || pistol->shots_boss[i].dy){
            frame %= BULLET_BOSS_ATTACK;
            sprite_draw = bullet_boss_sprites.attack[frame];
        }

        if(sprite_draw){
            al_draw_scaled_bitmap(
                    sprite_draw,                                                          // sprite original.
                    0, 0,                                                                 // coordenadas (x, y) de início.
                    al_get_bitmap_width(sprite_draw),                                     // largura original.
                    al_get_bitmap_height(sprite_draw),                                    // altura original.
                    pistol->shots_boss[i].x - camera_x, pistol->shots_boss[i].y,        // posição na tela.
                    al_get_bitmap_width(sprite_draw),                                 // largura.
                    al_get_bitmap_height(sprite_draw),                                // altura.
                    0);
        }
    }
}