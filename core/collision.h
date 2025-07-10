#ifndef COLLISION_H
#define COLLISION_H

struct ShotManager;
struct Player;
struct Boss;

// verifica colisão.
int collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2);

// colisão - projétil no inimigo - (diminui vida do inimigo e inutiliza o projétil).
void collide_shot_enemy(struct ShotManager *pistol, struct Player *player, int j);

// colisão - projétil inimigo no player - (diminui vida do player e inutiliza o projétil).
void collide_enemy_shot_player(struct ShotManager *pistol, struct Player *player, int i);

// colisão - player no inimigo - (diminui vida do player e reinicia o cooldown de invencibilidade).
void collide_player_enemy(struct Player *player);

// colisão - player no boss - (diminui vida do player e reinicia o cooldown de invencibilidade).
void collide_player_boss(struct Player *player, struct Boss *boss);

// colisão - projétil no boss - (diminui vida do inimigo e inutiliza o projétil).
void collide_shot_boss(struct ShotManager *pistol, struct Player *player, struct Boss *boss, int i);

// colisão - projétil do boss no player - (diminui vida do player e inutiliza o projétil).
void collide_boss_shot_player(struct ShotManager *pistol, struct Player *player, int i);

#endif