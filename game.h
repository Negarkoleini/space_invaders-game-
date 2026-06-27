#pragma once
#ifndef GAME_H
#define GAME_H

void startLevel();
void handleInput();
void checkLevelComplete();
void gameLoop();
void drawScore(int score, int level);
void drawHealth(int currentHp, int maxHp);

#endif;
