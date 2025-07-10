#ifndef BUTTONS_H
#define BUTTONS_H

#define MENU_BUTTONS 3
#define SETTINGS_BUTTONS 3
#define PAUSE_BUTTONS 2
#define GAMEOVER_BUTTONS 2
#define VICTORY_BUTTONS 2

// botão com posição e tamanho pré-definidos.
struct Button{
    float x, y;              // coordenada (x, y) do canto superior esquerdo do botão.
    float w, h;              // largura e altura do botão, respectivamente.
};

// grupo de botões.
struct ButtonGroup{
    struct Button *menu;
    struct Button *settings;
    struct Button *pause;
    struct Button *gameover;
    struct Button *victory;
};

// botão usando coordenadas proporcionais a tela (percentuais).
struct ButtonPerc{
    float x_perc, y_perc;    // coordendas (x, y) relativas do canto superior esquerdo do botão. 
    float w_perc, h_perc;    // largura e altura relativa do botão, respectivamente.
};

// verifica se uma coordenada (x, y) esta dentro da área do botão.
int is_inside_button(struct Button button, float position_x, float position_y);

// inicializa os botões, considerando o tamanho da tela atual.
void buttons_init(struct Button *buttons, int screen_width, int screen_height, int count, int termo);

#endif