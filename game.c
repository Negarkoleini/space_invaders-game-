#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <io.h>
#include <fcntl.h>
#include <locale.h>
#include <windows.h>
#include <wchar.h> 
#include "math.h"
#include <stdbool.h>
#include "map.h"
#include "player.h"
#include "common.h"
#include "enemy.h"
#include<windows.h>
#include "menu1.h"

#pragma warning(disable:4996)
// use wchar_t instead of char (for the special characters)
// use wprintf instead of printf (when printing special characters)
// and lastly make sure to set the stdout mode to u16 before using wprintf, and txt for printf (it might crash otherwise)

#define settxt _setmode(_fileno(stdout), _O_TEXT)
#define setu16 _setmode(_fileno(stdout), _O_U16TEXT)
#define sleep(x) Sleep(1 * (x))


void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


int level = 1;

int enemiesToSpawn;    // تعداد کل دشمن این مرحله
int enemiesSpawned;     // چند تا ساخته شده


// شروع مرحله جدید
void startLevel() {

    enemiesToSpawn = 3 * pow(level , 0.5);   // فرمول مرحله
    enemiesSpawned = 0;

    initEnemies();
}


// گرفتن ورودی
void handleInput() {

    if (_kbhit()) {

        char c = _getch();

        if (c == 'a') moveplayer(-1, 0);
        if (c == 'd') moveplayer(1, 0);
        if (c == 'w') moveplayer(0, -1);
        if (c == 's') moveplayer(0, 1);
        if (c == ' ') playershoot();
    }
}



void checkLevelComplete() {

    if (enemiesSpawned == enemiesToSpawn && currentenemies == 0) {

        level++;
        enemyspawned = 0;
        startLevel();
    }
}

void drawScore(int score, int level) {
    gotoxy(2, 0);
    settxt;

    

    
    printf("\x1b[33mSCORE: %d\x1b[0m | \x1b[36mLEVEL: %d\x1b[0m", score, level);
}

void drawHealth(int currentHp, int maxHp) {
    gotoxy(25, 0);
   settxt;

    
  
    printf("HP: ");

    
    char* color = "\x1b[32m";
    if (currentHp <= maxHp / 4) color = "\x1b[31m";      
    else if (currentHp <= maxHp / 2) color = "\x1b[33m"; 

    for (int i = 0; i < maxHp; i++) {
        if (i < currentHp)
            printf("%s\x1b[0m", color); 
        else
            printf("\x1b[90m-\x1b[0m"); 
    }

    printf(" %s%d/%d\x1b[0m", color, currentHp, maxHp);
}




void gameLoop() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    info.bVisible = FALSE; 
    SetConsoleCursorInfo(consoleHandle, &info);



    void hideCursor() {
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = FALSE; 
        SetConsoleCursorInfo(consoleHandle, &info);
    }


    reset();
    startLevel();

    while (player.hp > 0) {

        handleInput();

        updateplayer();
        updateEnemies();
        checkBulletCollision();

        
        if (enemiesSpawned < enemiesToSpawn) {
            spawnEnemy();
            enemiesSpawned++;
        }

        checkLevelComplete();
        gotoxy(33, 0);

        Map();
        drawMap();   

        drawScore(player.score, level);
        drawHealth(player.hp, 5);



        Sleep(50);
    }
    system("cls");

    printf("GAME OVER\n");
}
       






































