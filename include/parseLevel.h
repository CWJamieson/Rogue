#ifndef __CJAMIE04_PARSELEVEL__
#define __CJAMIE04_PARSELEVEL__

//includes
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>

/*
*   parseDataFile
*   stores data from the text file in level data
*   IN: string path to data file, reference to level memory array
*   POST: level file memory is allocated and filled
*   ERROR: if path is incorrect, an error is printed and program exits
*          if there is no memory left, the same as above happens
*/
void parseDataFile(char *, Map **);

#endif //end parseLevel.h
