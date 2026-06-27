#ifndef PLAYER_H
#define PLAYER_H

#define MAX_PLAYER_BULLETS 3

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    Position pos;
    int dx;        
    int dy;        
    int active;    
} Tir;

typedef struct {
    Position pos;
    int hp;
    int damage;
    int coin;
    int score;

    Tir tir[MAX_PLAYER_BULLETS];
    int nextBullet;   
} Player;

extern Player player;

void reset();
void moveplayer(int dx, int dy);
void playershoot();
void updateplayer();

void updateplayerBullets();

#endif
