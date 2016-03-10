#ifndef __CJAMIE04_DRAWMAP__
#define __CJAMIE04_DRAWMAP__

//includes
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "drawHalls.h"

/*
*   buildLevel
*   builds the level using ncurses, calling other functions to help
*   IN: The map data, and the player data
*   POST: calls draw for every room
*   ERROR: if the screen is not big enough, the program will end
*/
void buildLevel(Map **, Player *, Enemy **);

/*
*   draw
*   responcible for drawing a single room, using other fuctions
*   IN: level data, reference positions for the room (x and y), the
*        room number, and player data
*   POST: Calls drawRoom and draw Elements
*/
void draw(Map **, int, int, int, Player *, Enemy **, int *);

/*
*   drawRoom
*   draws the walls and floor for a given room
*   IN: points to the y and x reference position, and the width and
*        height of the room
*   POST: prints walls and floor to ncurses
          moves reference position to inside the walls
*/
void drawRoom(int *, int *, int, int);

/*
*   drawElements
*   draws the symbols into the rooms
*   IN: level data, x and y reference positions, player data, room
*        number, width and height of the room
*   POST: calls drawDoor(if needed), calls createPlayer(if needed)
*         calls getFig, prints symbols to room
*/
void drawElements(Map **, int, int, Player *, int, int, int, Enemy **, int *);

/*
*   drawDoor
*   draws the door to ncurses
*   IN: x and y reference positions, level data, room number, width
*        and height of the room, element number
*   POST: doors are drawn to ncurses
*/
void drawDoor(int, int, Map **, int, int, int, int);

/*
*   createPlayer
*   sets the initial player data
*   IN: hero starting position string, room number, player memory
*        location, level data, x and y room reference location
*   POST: player data is applied to memory
*/
void createPlayer(char *, int, Player *, Map **, int, int);

void createEnemy(char *, int, Enemy **, int, Map **, int, int);

/*
*   getFig
*   translates data file symbols to level symbols
*   IN: char to translate
*   OUT: symbol to be printed
*/
char getFig(char);



void drawBorder();

#endif //end of drawmap.h
