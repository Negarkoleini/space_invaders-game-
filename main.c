#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include "map.h"
#include "player.h"
#include "enemy.h"
#include "game.h"
#include "common.h"
#include "menu1.h"

int main() {
    char currentUser[50];
    int page = PAGE_LOGIN;
    hideCursor();
   
    while (1) {
        runMenu();
    }

   

 return 0;
}