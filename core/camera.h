#ifndef CAMERA_H
#define CAMERA_H

struct Player;
struct Display;

// retorna e atualiza a posição onde a 'câmera' do jogador irá ficar.
int camera_update(struct Player *player, struct Display *display);

#endif