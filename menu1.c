#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "enemy.h"
#include "player.h"
#include "map.h"
#include "menu1.h"
#include "game.h"   

void clear(void) {
    system("cls");
}

int page;
char currentUser[50];

#define PAGE_LOGIN   0
#define PAGE_MENU    1
#define PAGE_GAME    2
#define PAGE_SCORE   3


int userExists(char username[]) {
    FILE* f = fopen("users.txt", "r");
    if (!f)
        return 0;

    char u[50], p[50];
    while (fscanf(f, "%s %s", u, p) != EOF) {
        if (strcmp(u, username) == 0) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

int checkPassword(char username[], char password[]) {
    FILE* f = fopen("users.txt", "r");
    if (!f) return 0;

    char u[50], p[50];
    while (fscanf(f, "%s %s", u, p) != EOF) {
        if (strcmp(u, username) == 0 && strcmp(p, password) == 0) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void saveUser(char username[], char password[]) {
    FILE* f = fopen("users.txt", "a");
    fprintf(f, "%s %s\n", username, password);
    fclose(f);
}


void runMenu() {

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int choice;

    switch (page) {

        
    case PAGE_LOGIN: {

        char password[50], confirm[50];

        clear();
        SetConsoleTextAttribute(h, 12);
        printf("=== LOGIN ===\n");
        printf("Username: ");
        SetConsoleTextAttribute(h, 7);
        scanf("%s", currentUser);

        if (!userExists(currentUser)) {

            SetConsoleTextAttribute(h, 12);
            printf("User not found. Sign up\n");
            printf("Password: ");
            SetConsoleTextAttribute(h, 7);
            scanf("%s", password);
            printf("Confirm Password: ");
            scanf("%s", confirm);

            if (strcmp(password, confirm) != 0) {
                printf("Passwords do not match!\n");
                system("pause");
                page = PAGE_LOGIN;
            }
            else {
                saveUser(currentUser, password);
                printf("Signup successful!\n");
                system("pause");
                page = PAGE_MENU;
            }

        }
        else {

            printf("Password: ");
            scanf("%s", password);

            if (checkPassword(currentUser, password)) {
                printf("Login successful!\n");
                system("pause");
                page = PAGE_MENU;
            }
            else {
                printf("Wrong password!\n");
                system("pause");
                page = PAGE_LOGIN;
            }
        }

        break;
    }

                   
    case PAGE_MENU:

        clear();
        printf("Welcome %s\n\n", currentUser);
        printf("1. Start Game\n");
        printf("2. Logout\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1)
            page = PAGE_GAME;
        else
            page = PAGE_LOGIN;

        break;


        
    case PAGE_GAME:

        clear();
        gameLoop();   
        page = PAGE_MENU;  
        break;
    }
}