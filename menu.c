#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

void clear(void) {
    system("cls");
}

extern int page;
extern int selectedMap;
extern char currentUser[50];

#define PAGE_LOGIN       0
#define PAGE_SELECTMAP   1
#define PAGE_MAPMENU     2
#define PAGE_GAME        3
#define PAGE_SCORE       4


void clear();
void runsnake();
void drawMap1();
void drawMap2();

int userExists(char username[]) {
    FILE* f = fopen("users.txt", "r");
    if (f == 0)
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
            SetConsoleTextAttribute(h, 12);
            printf("Confirm Password: ");
            SetConsoleTextAttribute(h, 7);
            scanf("%s", confirm);

            if (strcmp(password, confirm) != 0) {
                SetConsoleTextAttribute(h, 12);
                printf("Passwords do not match!\n");
                system("pause");
                page = PAGE_LOGIN;
            }
            else {
                saveUser(currentUser, password);
                SetConsoleTextAttribute(h, 12);
                printf("Signup successful!\n");
                system("pause");
                page = PAGE_SELECTMAP;
            }

        }
        else {
            SetConsoleTextAttribute(h, 12);
            printf("User found. Login\n");
            printf("Password: ");
            SetConsoleTextAttribute(h, 7);
            scanf("%s", password);

            if (checkPassword(currentUser, password)) {
                SetConsoleTextAttribute(h, 12);
                printf("Login successful!\n");
                system("pause");
                page = PAGE_SELECTMAP;
            }
            else {
                printf("Wrong password!\n");
                system("pause");
                page = PAGE_LOGIN;
            }
        }
        break;
    }


    case PAGE_SELECTMAP:
        clear();
        printf("Welcome %s\n\n", currentUser);
        printf("1. Map 1\n");
        printf("2. Map 2\n");
        printf("3. Logout\n");
        printf("Choice: ");
        SetConsoleTextAttribute(h, 7);
        scanf("%d", &choice);

        if (choice == 1 || choice == 2) {
            selectedMap = choice;
            page = PAGE_MAPMENU;
        }
        else {
            page = PAGE_LOGIN;
        }
        break;


    case PAGE_MAPMENU:
        clear();
        SetConsoleTextAttribute(h, 12);
        printf("Map %d Menu\n\n", selectedMap);
        printf("1. Start Game\n");
        printf("2. Scores\n");
        printf("3. Back\n");
        printf("Choice: ");
        SetConsoleTextAttribute(h, 7);
        scanf("%d", &choice);

        if (choice == 1)
            page = PAGE_GAME;
        else if (choice == 2)
            page = PAGE_SCORE;
        else
            page = PAGE_SELECTMAP;
        break;


    case PAGE_GAME:
        clear();

        if (selectedMap == 1) {
            Map1();
            drawMap1();
        }
        else {
            Map2();
            drawMap2();
        }

        runsnake();
        page = PAGE_MAPMENU;
        break;


    }
}