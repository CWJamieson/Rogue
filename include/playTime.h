#ifndef __CJAMIE04_PLAYTIME__
#define __CJAMIE04_PLAYTIME__

//includes
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "movement.h"
#include "combat.h"

/*
*   playTime
*   manages the whole gameplay experience
*   IN: level data, and player data
*   POST: starts game loop, and runs functions based on input
*   ERROR: if no valid key is pressed, the loop will iterate again
*/
void playTime(Map **, Player *, Enemy **);

void usePotion(Player *);

/*
*   quitGame
*   exits the game safely
*   IN: player data, level data
*   POST: clears the memory for player and level, closes ncurses, quits
*/
void quitGame(Player *, Map **, Enemy **);

void moveText();



#endif //end playTime.h
