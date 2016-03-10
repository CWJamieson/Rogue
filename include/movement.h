#ifndef __CJAMIE04_MOVEMENT__
#define __CJAMIE04_MOVEMENT__

//includes
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>
#include "playTime.h"
#include "combat.h"

/*
*   actionReader
*   handles all valid keys except quit
*   IN: player data, map data, x and y reference pointers, width and
*        height pointers, and the change in x and y
*   OUT: 1 if cannot move, 0 if sucess
*   POST: calls objectCheck, and moveplayer or levelUp if applicable
*   ERROR: if unable to move, returns early
*/
int actionReader(Player *, Map **, int *, int *, int *, int *, int, int, Enemy **);


/*
*   objectCheck
*   checks for a monster or collectable
*   IN: player data, level data, x and y position for location to check
*   OUT: 1 if cannot move, 0 if can
*   POST: adds collectable to player if applicable, prints collectable
            message to screen
*/
int objectCheck(Player *, Map **, int, int, int *, int *, int *, int *, Enemy **);

/*
*   movePlayer
*   chanfes the player position
*   IN: player data, x and y change values
*   POST: changes x and y position in character data
*          prints new character to the screen and erases old one
*/
void movePlayer(Player *, int, int);

#endif
