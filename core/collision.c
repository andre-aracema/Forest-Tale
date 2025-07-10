#include "player.h"
#include "boss.h"
#include "enemy.h"
#include "shot.h"
#include "collision.h"

int collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2){
    if(ax1 > bx2)   // A está à direita de B.
        return 0;    
    if(ax2 < bx1)   // A está à esquerda de B.
        return 0;
    if(ay1 > by2)   // A está abaixo de B.
        return 0;
    if(ay2 < by1)   // A está acima de B.
        return 0;

    return 1;       // há sobreposição.  
}

void collide_shot_enemy(struct ShotManager *pistol, struct Player *player, int j){
    // verifica colisão com inimigo.
    struct Enemy *enemies = enemies_get();

    for(int i = 0; i < ENEMY_MAX; i++){
        if(enemies[i].lives == 0)
            continue;

        // centralizando hitbox para o meio da sprite.
        int ax1 = pistol->shots[j].x + (pistol->shots[j].width - pistol->shots[j].col_w) / 2 + pistol->shots[j].offset_up;
        int ay1 = pistol->shots[j].y + (pistol->shots[j].height - pistol->shots[j].col_h) / 2 + pistol->shots[j].offset_up;
        int ax2 = ax1 + pistol->shots[j].col_w;                             // largura do tiro.
        int ay2 = ay1 + pistol->shots[j].col_h;

        // arrumando hitbox.
        int bx1 = enemies[i].x + 18;
        int by1 = enemies[i].y + 15;
        int bx2 = bx1 + enemies[i].width;
        int by2 = by1 + enemies[i].height;

        if(collide(ax1, ay1, ax2, ay2, bx1, by1, bx2, by2)){
            pistol->shots[j].used = 0;
            enemies[i].lives--;
            enemies[i].damage_cooldown = 5;

            if(enemies[i].lives <= 0)
                player->score += 100;

            break;
        }
    }
}

void collide_enemy_shot_player(struct ShotManager *pistol, struct Player *player, int i){
    // centralizando hitbox para o meio da sprite.
    int ax1 = pistol->shots_enemy[i].x + (pistol->shots_enemy[i].width - pistol->shots_enemy[i].col_w) / 2;
    int ay1 = pistol->shots_enemy[i].y + (pistol->shots_enemy[i].height - pistol->shots_enemy[i].col_h) / 2;
    int ax2 = ax1 + pistol->shots_enemy[i].col_w;                             
    int ay2 = ay1 + pistol->shots_enemy[i].col_h;

    // arrumando hitbox.
    // bordas do jogador
    int bx1 = player->x + 10;
    int by1 = player->y + 15 + player->offset_crouched;
    int bx2 = player->x + player->width;
    int by2 = player->y + player->height;

    if(collide(ax1, ay1, ax2, ay2, bx1, by1, bx2, by2)){
        if((player->damage_cooldown == 0) && (player->lives > 0)){
            pistol->shots_enemy[i].used = 0;
            player->lives--;
            player->damage_cooldown = 60;
        }
    }
}

void collide_player_enemy(struct Player *player){
    // verifica colisão com inimigo.
    struct Enemy *enemies = enemies_get();

    for(int i = 0; i < ENEMY_MAX; i++){
        if(enemies[i].lives == 0)
            continue;

        // bordas do jogador
        int ax1 = player->x + 10;
        int ay1 = player->y + 15 + player->offset_crouched;
        int ax2 = player->x + player->width;
        int ay2 = player->y + player->height;

        // bordas do inimigo
        int bx1 = enemies[i].x + 18;
        int by1 = enemies[i].y + 15;
        int bx2 = bx1 + enemies[i].width;
        int by2 = by1 + enemies[i].height;

        if(collide(ax1, ay1, ax2, ay2, bx1, by1, bx2, by2)){
            if((player->damage_cooldown == 0) && (player->lives > 0)){
                player->lives--;
                player->damage_cooldown = 60;
            }
        }
    }
}

void collide_player_boss(struct Player *player, struct Boss *boss){
    // bordas do jogador
    int ax1 = player->x + 10;
    int ay1 = player->y + 15 + player->offset_crouched;
    int ax2 = player->x + player->width;
    int ay2 = player->y + player->height;

    // bordas do boss.
    int bx1 = boss->x + 160;
    int by1 = boss->y + 180;
    int bx2 = bx1 + boss->width - 40;
    int by2 = by1 + boss->height - 60;

    if(collide(ax1, ay1, ax2, ay2, bx1, by1, bx2, by2)){
        if((player->damage_cooldown == 0) && (player->lives > 0)){
            player->lives--;
            player->damage_cooldown = 60;
        }
    }
}

void collide_shot_boss(struct ShotManager *pistol, struct Player *player, struct Boss *boss, int i){
    // centralizando hitbox para o meio da sprite.
    int ax1 = pistol->shots[i].x + (pistol->shots[i].width - pistol->shots[i].col_w) / 2 + pistol->shots[i].offset_up;
    int ay1 = pistol->shots[i].y + (pistol->shots[i].height - pistol->shots[i].col_h) / 2 + pistol->shots[i].offset_up;
    int ax2 = ax1 + pistol->shots[i].col_w;                             // largura do tiro.
    int ay2 = ay1 + pistol->shots[i].col_h;

    // bordas do boss.
    int bx1 = boss->x + 160;
    int by1 = boss->y + 180;
    int bx2 = bx1 + boss->width - 40;
    int by2 = by1 + boss->height - 60;

    if((collide(ax1, ay1, ax2, ay2, bx1, by1, bx2, by2)) && !boss->sleep){
        pistol->shots[i].used = 0;
        boss->lives--;
        boss->damage_cooldown = 5;

        if(boss->lives <= 0)
            player->score += 5000;
    }
}

void collide_boss_shot_player(struct ShotManager *pistol, struct Player *player, int i){
    // centralizando hitbox para o meio da sprite.
    int ax1 = pistol->shots_boss[i].x + (pistol->shots_boss[i].width - pistol->shots_boss[i].col_w) / 2 + pistol->shots_boss[i].offset_up;
    int ay1 = pistol->shots_boss[i].y + (pistol->shots_boss[i].height - pistol->shots_boss[i].col_h) / 2 + pistol->shots_boss[i].offset_up;
    int ax2 = ax1 + pistol->shots_boss[i].col_w;                             // largura do tiro.
    int ay2 = ay1 + pistol->shots_boss[i].col_h;

    // arrumando hitbox.
    // bordas do jogador
    int bx1 = player->x + 10;
    int by1 = player->y + 15 + player->offset_crouched;
    int bx2 = player->x + player->width;
    int by2 = player->y + player->height;

    if(collide(ax1, ay1, ax2, ay2, bx1, by1, bx2, by2)){
        if((player->damage_cooldown == 0) && (player->lives > 0)){
            pistol->shots_boss[i].used = 0;
            player->lives--;
            player->damage_cooldown = 60;
        }
    }
}
