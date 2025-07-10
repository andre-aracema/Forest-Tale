#include <allegro5/allegro.h>

#include "display.h"
#include "background.h"

void background_game_update(ALLEGRO_BITMAP *bitmap, struct Display *display, int camera_x){
    // vezes que o bitmap deve ser desenhado horizontalmente para cobrir o cenário.
    int count = display->background_game / display->width + 2;

    for (int i = 0; i < count; i++) {
        // posição x onde a imagem será desenhada na tela.
        int dest_x = i * display->width - camera_x;

        // verifica se a imagem esta 'dentro' da tela.
        if((dest_x + display->width >= 0) && (dest_x <= display->width)){
            al_draw_scaled_bitmap(
                            bitmap,                           // 1. imagem a ser desenhada.
                            0, 0,                             // 2. coordenadas (x, y) da posição inicila da imagem.
                            al_get_bitmap_width(bitmap),      // 3. largura da região da imagem que será desenhada.
                            al_get_bitmap_height(bitmap),     // 4. altura da região da imagem que será desenhada.
                            dest_x, 0,                        // 5. coordenadas (x, y) na tela onde o bitmap será desenhado.
                            display->width,                   // 6. largura final que a imagem terá na tela.
                            display->height,                  // 7. altura final que a imagem terá na tela.
                            0);                               // 8. flags. (apenas escalonamento).
        }
    }
}

void background_state_update(ALLEGRO_BITMAP *bitmap, struct Display *display){
    al_draw_scaled_bitmap(
                    bitmap,                                   // 1. imagem a ser desenhada.
                    0, 0,                                     // 2. coordenadas (x, y) da posição inicila da imagem.
                    al_get_bitmap_width(bitmap),              // 3. largura da região da imagem que será desenhada.
                    al_get_bitmap_height(bitmap),             // 4. altura da região da imagem que será desenhada.
                    0, 0,                                     // 5. coordenadas (x, y) na tela onde o bitmap será desenhado.
                    display->width,                           // 6. largura final que a imagem terá na tela.
                    display->height,                          // 7. altura final que a imagem terá na tela.
                    0);                                       // 8. flags. (apenas escalonamento).
}