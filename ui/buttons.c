#include "buttons.h"

// somente para cálculos.
struct ButtonPerc buttons_perc[3] = {
    {0.446875, 0.5444, 0.109375, 0.0555},
    {0.4125,   0.6333, 0.175,    0.0555},
    {0.45625,  0.7333, 0.0875,   0.0555}
};

// verifica se uma coordenada (x, y) esta dentro da área do botão.
int is_inside_button(struct Button button, float position_x, float position_y){
    return ((position_x >= button.x) && 
            (position_x <= button.x + button.w) && 
            (position_y >= button.y) && 
            (position_y <= button.y + button.h));
}

// inicializa os botões, considerando o tamanho da tela atual.
void buttons_init(struct Button *buttons, int screen_width, int screen_height, int count, int termo){
    for(int i = 0; i < count; i++){
        buttons[i].x = buttons_perc[i + termo].x_perc * screen_width;
        buttons[i].y = buttons_perc[i + termo].y_perc * screen_height;
        buttons[i].w = buttons_perc[i + termo].w_perc * screen_width;
        buttons[i].h = buttons_perc[i + termo].h_perc * screen_height;
    }
}