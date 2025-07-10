#ifndef BACKGROUND_H
#define BACKGROUND_H

struct Display;

/**
 * desenha o background do jogo repetindo o bitmap horizontalmente (eixo x) para
 * cobrir a largura total do cenário ('total_width') aplicando deslocamento ('camera_x')
 * para simular o movimento de camêra.
 * O background é escalonado para preencher a área visível (display).
 */
void background_game_update(ALLEGRO_BITMAP *bitmap, struct Display *display, int camera_x);

// desenha o background redimensionado para preencher a área visível (display).
void background_state_update(ALLEGRO_BITMAP *bitmap, struct Display *display);

#endif