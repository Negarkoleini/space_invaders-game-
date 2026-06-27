#include "map.h"
#include <wchar.h>
#include <windows.h>
#include <io.h> 
#include <fcntl.h>
#include "enemy.h"
#include "player.h"
#include <stdio.h> 
#include "common.h"
#define setu16 _setmode(_fileno(stdout), _O_U16TEXT)
int map[HEIGHT][WIDTH];
extern Player player;
extern Enemy enemies[MAX_ENEMIES];

void Map() {
	for (int i = 1; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			if ( j == WIDTH - 1 || j == 0 || i == HEIGHT - 1 || i == HEIGHT - 2 || i == 1)
				map[i][j] = 1;
			else
				map[i][j] = 0;
		}
	}
}
void drawMap() {

    setu16;

    for (int i = 0; i < HEIGHT; ++i) {

        for (int j = 0; j < WIDTH; ++j) {

            int drawn = 0;

            
            if (player.pos.x == j && player.pos.y == i) {
                wprintf(L"\u25CF");  // ●
                drawn = 1;
            }

            
            for (int k = 0; k < MAX_ENEMIES; k++) {
                if (enemies[k].active == 1 && enemies[k].pos.x == j && enemies[k].pos.y == i ) {

                    wprintf(L"\u25A0"); // ■
                    drawn = 1;
                    break;
                }
            }

            
            for (int b = 0; b < 3; b++) {
                if (map[i][j] == 0 &&player.tir[b].active && player.tir[b].pos.x == j && player.tir[b].pos.y == i && player.tir[b].active == 1) {
             
                    wprintf(L"|");
                    drawn = 1;
                    break;
                }
            }

            
            if (!drawn) {
                if (map[i][j] == 1)
                    wprintf(L"\u2588"); // █
                else
                    wprintf(L" ");
            }
        }

        wprintf(L"\n");
    }
}