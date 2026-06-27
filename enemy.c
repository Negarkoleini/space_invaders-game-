#include <stdlib.h>
#include <math.h>  
#include <stdbool.h>
#include "enemy.h"
#include "player.h"
#include "map.h"
#include "common.h"
#include "game.h"
extern int level;
//extern int max_enemies;

//#define maxs_enemies 100   

Enemy enemies[MAX_ENEMIES];
int currentenemies = 0;
int enemyspawned = 0;
int gametick = 0;

void initEnemies() {
	for (int i = 0; i < MAX_ENEMIES; ++i)
		enemies[i].active = 0;

	int currentenemies = 0;
}

double maxenemies(int level) {
	return 3 * pow(level, 0.5);
}

void spawnEnemy() {
	if ( enemyspawned >= maxenemies(level))
		return;

	for (int i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i].active == 0) {
			int temp = rand() % WIDTH;
            
         /*   for (int j = 0; j < maxenemies(level); ++j) {
                if (temp == enemies[j].pos.x && enemies[j].pos.y == 0 ) {
                    temp = rand() % WIDTH;
                }
            }*/


            enemies[i].pos.x = temp;
            enemies[i].pos.y = 3;
            enemies[i].hp = 2 + (level / 10);
            enemies[i].damage = 1 + (level / 20);
            enemies[i].active = 1;

            currentenemies++;
            enemyspawned++;

            break;

		}

	}
}



void updateEnemies() {

    if (gametick % 3 != 0) {
        ++gametick;
        return;
    }

    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) continue;

        int dx = player.pos.x - enemies[i].pos.x;
        int dy = player.pos.y - enemies[i].pos.y;
        int absDx = abs(dx);
        int absDy = abs(dy);

        
        if (absDx <= 1 && absDy <= 1) {
            player.hp -= enemies[i].damage;
            continue;
        }

        int nextX = enemies[i].pos.x;
        int nextY = enemies[i].pos.y;

        
        int decision = rand() % 100;

        if (decision < 70) {
            
            if (absDx > absDy) {
                nextX += (dx > 0) ? 1 : -1;
            }
            else {
                nextY += (dy > 0) ? 1 : -1;
            }
        }
        else if (decision < 90) {
            
            int randomDir = rand() % 4;
            if (randomDir == 0) nextX++;
            else if (randomDir == 1) nextX--;
            else if (randomDir == 2) nextY++;
            else if (randomDir == 3) nextY--;
        }
        

        
        bool canMove = true;

        
        if (nextX <= 0 || nextX >= WIDTH - 1 || nextY <= 0 || nextY >= HEIGHT - 1) {
            canMove = false;
        }

        
        if (canMove) {
            for (int j = 0; j < MAX_ENEMIES; j++) {
                if (i != j && enemies[j].active) {
                    if (enemies[j].pos.x == nextX && enemies[j].pos.y == nextY) {
                        canMove = false;
                        break;
                    }
                }
            }
        }

        
        if (canMove) {
            enemies[i].pos.x = nextX;
            enemies[i].pos.y = nextY;
        }
    }
    ++gametick;
}



void checkBulletCollision() {

    for (int i = 0; i < MAX_ENEMIES; i++) {

        if (!enemies[i].active)
            continue;

        for (int j = 0; j < 3; j++) {

            if (!player.tir[j].active)
                continue;

            if (player.tir[j].pos.x == enemies[i].pos.x && player.tir[j].pos.y == enemies[i].pos.y) {

                enemies[i].hp -= player.damage;
                player.tir[j].active = 0;


                if (enemies[i].hp <= 0) {
                    enemies[i].active = 0;
                    currentenemies--;
                    player.score += 10;
                }
            }
        }
    }
}
