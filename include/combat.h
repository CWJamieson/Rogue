#ifndef __CJAMIE04_COMBAT__
#define __CJAMIE04_COMBAT__

//includes
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>
#include "playTime.h"
#include "movement.h"


void combat(int, int, Player *, Enemy **);

void moveEnemies(Enemy **, Player *);

void enemyObjChk(Enemy **, int, int, int, Player *);

char * getWord(char);

#endif
