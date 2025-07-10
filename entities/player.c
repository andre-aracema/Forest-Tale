#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "system.h"
#include "collision.h"
#include "display.h"
#include "sprites_player.h"
#include "sprites_bullet.h"
#include "item.h"
#include "shot.h"
#include "boss.h"
#include "player.h"

struct Player *player_create(struct Display *display){
    // tamanho do player.
    int player_height = display->height * PLAYER_HEIGHT_PERC;
    int player_width = display->width * PLAYER_WIDTH_PERC;
    
    int x = display->width * 0.09;
    int y = display->height * FLOOR_PLAYER - player_height; 
    
    // verifica se o jogador esta 'dentro' da tela.
    if((x - player_width / 2 < 0) || (x + player_width / 2 > display->width) || (y - player_height / 2 < 0) || (y + player_height / 2 > display->height)){
        return NULL;
    }
    
    struct Player *new_player = (struct Player*)malloc(sizeof(struct Player));
    if(!new_player){
        return NULL;
    }

    new_player->x = x;
    new_player->y = y;
    new_player->width = player_width;
    new_player->height = player_height;
    new_player->lives = PLAYER_LIVES;
    new_player->speed_y = 0;
    new_player->damage_cooldown = 25;
    new_player->last_dx = RIGHT;
    new_player->last_dy = NEUTRO;
    new_player->attack = 0;
    new_player->walk = 0;
    new_player->crouched = 0;
    new_player->sprite_dir = RIGHT;
    new_player->anim_frame = 0;
    new_player->anim_counter = 0;
    new_player->last_state = 0;
    new_player->ground = y;
    new_player->offset_crouched = 0;
    new_player->ammunition = 10;
    new_player->reloading = 0;
    new_player->score = 0;
    new_player->double_jump = 0;
    new_player->jump_count = 0;
    new_player->jump_pressed = 0;
    
    return new_player;
}

void player_destroy(struct Player *player){
    free(player);
}

void player_update(struct Player *player, struct Display *display, struct ShotManager *pistol, struct Boss *boss){
    player->walk = 0;
    player->crouched = 0;
    player->attack = 0;
    int current_state = 0;

    // sprite.
    player->anim_counter++;
    if(player->anim_counter >= 8){
        player->anim_counter = 0;
        player->anim_frame++;
    }
    
    if(player->lives > 0){
        if(key[ALLEGRO_KEY_A]){
            player->x -= PLAYER_STEP;                        // movimentação.
            player->last_dx = LEFT;                          // posição do tiro.
            player->last_dy = NEUTRO;                        // posição do tiro.
            player->walk = 1;                                // movimentação (sprite).
            player->sprite_dir = LEFT;                       // movimentação (sprite).
        }
        if(key[ALLEGRO_KEY_D]){
            player->x += PLAYER_STEP;                        // movimentação.
            player->last_dx = RIGHT;                         // posição do tiro.
            player->last_dy = NEUTRO;                        // posição do tiro.
            player->walk = 1;                                // movimentação (sprite).
            player->sprite_dir = RIGHT;                      // movimentação (sprite).
        }
        if(key[ALLEGRO_KEY_W]){  
            player->last_dx = NEUTRO;                        // posição do tiro.
            player->last_dy = UP;                            // posição do tiro.
        }

        if((key[ALLEGRO_KEY_S]) && (player->walk == 0)){      
            player->crouched = 1;
            current_state = 3;                            // crounched
        }

        // disparo.
        if((mouse[1]) && (player->reloading == 0) && 
            (player->ammunition > 0) && (player->shot_cooldown == 0)){
            player_shot_update(pistol, player);
            player->attack = 1;
            current_state = 5;                            // attack.
            player->ammunition--;
        }

        // pulando.
        if((key[ALLEGRO_KEY_SPACE]) && (player->jump_pressed == 0)){
            // primeiro pulo (não é necessário ter bota).
            if(player->jump_count == 0){
                player->speed_y = -35;
                player->jump_count = 1;
            }
            // segundo salto (necessário ter bota).
            else if((player->double_jump) && (player->jump_count == 1)){
                player->speed_y = -35;
                player->jump_count = 2;
            }

            player->jump_pressed = 1;
        }

        if(!key[ALLEGRO_KEY_SPACE])
            player->jump_pressed = 0;
            
    }

    // estados.
    if((player->walk) && (player->speed_y == 0) && (!player->crouched))
        current_state = 1;                               // walk.
    
    if(player->speed_y != 0)
        current_state = 2;                               // jump.

    if(player->lives <= 0)
        current_state = 4;                               // dead.

    // garante que personagem não saia da tela.
    if(player->x < 0)
        player->x = 0;

    if(player->x > display->background_game - player->width)
        player->x = display->background_game - player->width;

    // gravidade.
    int gravity = 3;

    // aplica gravidade ao jogador.
    player->speed_y += gravity;
    player->y += player->speed_y;

    // colisão com o solo (chão).
    if(player->y >= player->ground){
        player->y = player->ground;     // fixa no chão.
        player->speed_y = 0;            // para a queda. 
        player->jump_count = 0;   
    }

    // colisão com inimigo (corpo a corpo).
    collide_player_enemy(player);
    collide_player_boss(player, boss);
    
    // recarga de projétil.
    if((player->ammunition <= 0) && (player->reloading == 0))
        player->reloading = PLAYER_RELOAD_SHOT;

    // diminuindo recarga.
    if(player->reloading > 0){
        player->reloading--;

        // recarregado.
        if((player->reloading == 0) && (player->ammunition < 10)){
            player->ammunition++;
            
            // se ainda não completou.
            if(player->ammunition < 10){
                player->reloading = PLAYER_RELOAD_SHOT;
            }
        } 
    }

    // diminuindo cooldown de dano.
    if(player->damage_cooldown > 0)
        player->damage_cooldown--;

    // zerando index do frame.
    if(current_state != player->last_state){
        player->anim_frame = 0;
        player->anim_counter = 0;
        player->last_state = current_state;
    }
}

void player_draw(struct Player *player, struct Display *display, int camera_x){
    int screen_x;
    player->offset_crouched = 0;

    // câmera no início do cenário. Posição do jogador com coordendas do jogador.
    if(camera_x == 0)
        screen_x = player->x;
    
    // câmera no final do cenário. Posição do jogador com base na câmera.
    else if(camera_x == display->background_game - display->width)
        screen_x = player->x - camera_x;
    
    // câmera no meio do cenário. Fixa jogador no meio da tela.
    else
        screen_x = display->width / 2;

    // efeito de piscar quando toma dano.
    int visible = 1;
    if((player->damage_cooldown > 0) && (player->lives > 0)){
        if((player->damage_cooldown / 5) % 2 == 0)
            visible = 0; 
    }
    
    // sprite.
    int frame = player->anim_frame;
    ALLEGRO_BITMAP *sprite_draw = NULL;

    // escolhendo sprite de acordo com a direção.
    if(player->sprite_dir == LEFT){
        // atirando.
        if(player->attack){
            visible = 1;
            frame = 4;
            if(player->crouched)
                sprite_draw = player_sprites_l.crouched[frame];
            else
                sprite_draw = player_sprites_l.attack[frame];
        }
        // morrendo.
        else if(player->lives <= 0){
            frame %= PLAYER_DIED;
            sprite_draw = player_sprites_l.died[frame];
        }
        // pulando.
        else if(player->speed_y != 0){
            frame %= PLAYER_JUMP;
            if(player->speed_y >= 0){
                frame = 5;
            }
            sprite_draw = player_sprites_l.jump[frame];
        }
        // agachando.
        else if(player->crouched){
            player->offset_crouched = 15;
            frame = 2;
            sprite_draw = player_sprites_l.crouched[frame];
        }
        // andando para esquerda.
        else if(player->walk){
            frame %= PLAYER_WALK; 
            sprite_draw = player_sprites_l.walk[frame];
        }
        // parado.
        else{
            frame %= PLAYER_IDLE;
            sprite_draw = player_sprites_l.idle[frame];
        }
    }
    else if(player->sprite_dir == RIGHT){
        // atirando.
        if(player->attack){
            visible = 1;
            frame = 4;
            if(player->crouched)
                sprite_draw = player_sprites_r.crouched[frame];
            else
                sprite_draw = player_sprites_r.attack[frame];
        }
        // morrendo.
        else if(player->lives <= 0){
            frame %= PLAYER_DIED;
            sprite_draw = player_sprites_r.died[frame];
        }
        // pulando.
        else if(player->speed_y != 0){
            frame %= PLAYER_JUMP;
            if(player->speed_y >= 0){
                frame = 5;
            }
            sprite_draw = player_sprites_r.jump[frame];
        }
        // agachando.
        else if(player->crouched){
            player->offset_crouched = 15;
            frame = 2;
            sprite_draw = player_sprites_r.crouched[frame];
        }
        // andando para direita.
        else if(player->walk){
            frame %= PLAYER_WALK; 
            sprite_draw = player_sprites_r.walk[frame];
        }
        // parado.
        else{
            frame %= PLAYER_IDLE;
            sprite_draw = player_sprites_r.idle[frame];
        }
    }

    if(visible && sprite_draw && (player->lives >= 0 || player->anim_frame < PLAYER_DIED)){
        al_draw_scaled_bitmap(
                    sprite_draw,                                   // sprite original.
                    8, 5,                                          // coordenadas (x, y) de início.
                    al_get_bitmap_width(sprite_draw),              // largura original.
                    al_get_bitmap_height(sprite_draw),             // altura original.
                    screen_x, player->y,                           // posição na tela.
                    al_get_bitmap_width(sprite_draw),              // largura.
                    al_get_bitmap_height(sprite_draw),             // altura.
                    0);                                            // flags.
    }
}

void player_status_draw(struct Player *player, struct Item *items, float time){
    // auxilia no desenho do sprite.
    static int frame_index = 0;
    static int frame_counter = 0;
    static int frame_bullet_index = 0;
    static int frame_bullet_counter = 0;
    int total_frames = 2;
    float offset;

    // atualiza a animação do retrato.
    frame_counter++;
    if (frame_counter >= 12) {
        frame_counter = 0;
        frame_index = (frame_index + 1) % total_frames;     // ciclo.
    }

    // atualiza a animação do reload.
    frame_bullet_counter++;
    if (frame_bullet_counter >= 6) {
        frame_bullet_counter = 0;
        frame_bullet_index = (frame_bullet_index + 1) % BULLET_ATTACK_UP;     // ciclo.
    }

    // posição na tela.
    int space = 30;
    
    // quantidade de corações máximos.
    int total_hearts = 5;

    int total_half = player->lives;     // 1 coração equivale a 2 vidas.
    
    for(int i = 0; i < total_hearts; i++){
        // coordenadas na tela.
        int x = 140 + space + i * HEART_SIZE;    // posição horizontal.
        int y = 60;

        // 4 meois por coração.
        int half_heart = total_half - i * 2;

        // sprite.
        ALLEGRO_BITMAP *sprite_draw = NULL;

        // coração cheio.
        if(half_heart >= 2)
            sprite_draw = player_sprites_h.heart[0];
            
        // coração 1/2.
        else if(half_heart >= 1)
            sprite_draw = player_sprites_h.heart[2];
            
        // coração vazio.
        else
            sprite_draw = player_sprites_h.heart[4];

        // efeito de flutuar utilizando seno.
        offset = 0.5 * sin(time * 10 + i);

        if(sprite_draw){
            al_draw_scaled_bitmap(
                                sprite_draw,      
                                0, 0,            
                                al_get_bitmap_width(sprite_draw),   
                                al_get_bitmap_height(sprite_draw),  
                                x, y + offset,    
                                65,        
                                65,       
                                0);
        }
    }

    // retrato animido.
    ALLEGRO_BITMAP *sprite_draw_f = player_sprites_h.f[frame_index];
    if(player->lives <= 0)
        sprite_draw_f = player_sprites_h.f[2];
    
    if(sprite_draw_f){
        al_draw_scaled_bitmap(
                    sprite_draw_f,                                 // sprite original.
                    0, 0,                                          // coordenadas (x, y) de início.
                    al_get_bitmap_width(sprite_draw_f),            // largura original.
                    al_get_bitmap_height(sprite_draw_f),           // altura original.
                    10, 10,                                        // posição na tela.
                    200, 200,                                      // largura, altura.
                    0);                                            // flags.
    }

    // balas.
    for(int i = 0; i < BULLET_ATTACK; i++){
        int x = 120 + i * 30;    // posição horizontal.
        int y = 70;

        ALLEGRO_BITMAP *sprite_bullet = NULL;

        if(i < player->ammunition){
            if(frame_bullet_index < 4)
                frame_bullet_index = 4;
            sprite_bullet = bullet_sprites_u.attack[frame_bullet_index];
        }
        else   
            sprite_bullet = player_sprites_h.heart[4];

        if(sprite_bullet)
            al_draw_scaled_bitmap(
                                sprite_bullet,      
                                0, 0,            
                                al_get_bitmap_width(sprite_bullet),   
                                al_get_bitmap_height(sprite_bullet),  
                                x, y,    
                                170,        
                                170,       
                                0);;
    }

    // itens coletados.
    if(player->double_jump){
        ALLEGRO_BITMAP *sprite_items = items[2].sprite;

        // efeito de flutuar utilizando seno.
        offset = 0.7 * sin(time * 10);

        if(sprite_items)
            al_draw_scaled_bitmap(
                                sprite_items,      
                                0, 0,            
                                al_get_bitmap_width(sprite_items),   
                                al_get_bitmap_height(sprite_items),  
                                100, 190 + offset,    
                                -40,        
                                40,       
                                0);;
    }
}