#include <allegro5/allegro.h>
#include "display.h"
#include "player.h"
#include "camera.h"

int camera_update(struct Player *player, struct Display *display){
    // posição inicial da câmera centralizando-a no player.
    int camera_x = player->x - display->width / 2;

    // evita ultrapassar os limites do cenário.
    if(camera_x < 0){
        camera_x = 0;
    }
    if(camera_x > display->background_game - display->width){
        camera_x = display->background_game - display->width;
    }

    return camera_x;
}