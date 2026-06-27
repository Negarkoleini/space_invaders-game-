#pragma once
#ifndef MENU1_H
#define MENU1_H


#define PAGE_LOGIN   0
#define PAGE_MENU    1
#define PAGE_GAME    2
#define PAGE_SCORE   3


extern int page;
extern char currentUser[50];


void runMenu(void);

#endif