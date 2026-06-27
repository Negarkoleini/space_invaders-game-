#include <stdlib.h>
#include <math.h>  
#include "enemy.h"
#include "player.h"
#include "map.h"
#include "common.h"

Player player;



void reset() {
    player.pos.x = 31;
    player.pos.y = 25;
    player.hp = 5;
    player.damage = 1;
    player.coin = 0;
    player.score = 0;
    player.nextBullet = 0;

    for (int i = 0; i < 3; ++i)
        player.tir[i].active = 0;
}

void moveplayer(int dx, int dy) {
    int nx = player.pos.x +dx;
    int ny = player.pos.y +dy;
    if (nx >= 0 && nx < WIDTH)
        player.pos.x = nx;

    if (ny >= 0 && ny < HEIGHT)
        player.pos.y = ny;
}

void playershoot() {
    int i = player.nextBullet;

    player.tir[i].pos = player.pos;
    player.tir[i].dx = 0;
    player.tir[i].dy = -1;
    player.tir[i].active = 1;

    player.nextBullet = (player.nextBullet + 1) % 3;

}

void updateplayer() {
    updateplayerBullets();
}

void updateplayerBullets() {
    for (int i = 0; i < 3; ++i) {
        if (player.tir[i].active == 0)
            continue;
        player.tir[i].pos.y += player.tir[i].dy;

        if (player.tir[i].pos.y < 0)
            player.tir[i].active = 0;

    }






}