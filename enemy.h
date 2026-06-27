#ifndef ENEMY_H
#define ENEMY_H
#define MAX_ENEMIES 100   

typedef struct {
    int x;
    int y;
} Positions;

//extern int max_enemies = 100;

typedef struct {
    Positions pos;
    int hp;
    int damage;
    int active;
} Enemy;

extern Enemy enemies[MAX_ENEMIES];
extern int currentenemies;
extern int enemyspawned;

void initEnemies();
double maxenemies(int level);
void spawnEnemy();
void updateEnemies();
void checkBulletCollision();
#endif
