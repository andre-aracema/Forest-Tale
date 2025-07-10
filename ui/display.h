#ifndef DISPLAY_H
#define DISPLAY_H

// estrutura que armazena informações do display.
struct Display{
    ALLEGRO_DISPLAY *display;             // tala em si.
    int width, height;                    // largura e altura do display, respectivamente.
    int background_game;                  // tamanho total do background utilizado no jogo.
    int fullscreen;                       // 1 = fullscreen; 0 = janela.
    int x_text, y_text;                   // posição da pontuação.
};

// cria o display.
void display_init(struct Display *data, int fullscreen);

// destroi o display.
void display_destroy(struct Display *display);

// atualiza o display.
void display_update(struct Display *display, int fullscreen);

#endif