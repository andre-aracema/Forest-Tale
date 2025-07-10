#include <allegro5/allegro.h>
#include "display.h"

void display_init(struct Display *data, int fullscreen){
    // configuração para melhor desempenho.
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    if(fullscreen){
        al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    }else{
        al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    }

    // cria novo display.
    data->display = al_create_display(1600, 900);    // tamanho recomendado.
    if(!data->display){
        exit(1);
    }

    // dados do display.
    data->width = al_get_display_width(data->display);
    data->height = al_get_display_height(data->display);
    data->background_game = data->width * 4;
    data->fullscreen = fullscreen;
    data->x_text = data->width * 0.9;
    data->y_text = data->height * 0.05;
}

void display_destroy(struct Display *display){
    if(display->display){
        al_destroy_display(display->display);
        display->display = NULL;
    }
}

void display_update(struct Display *display, int fullscreen){
    display_destroy(display);
    display_init(display, fullscreen);
}
