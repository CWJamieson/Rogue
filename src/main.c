/*
*   Program: A3
*   Programmer: Christopher Jamieson
*   Date: March 8th 2016
*   Program Description: A rouge-like dungeon crawler
*/

//includes
#include "structs.h"
#include "playTime.h"
#include "drawMap.h"
#include "parseLevel.h"


/*
*   main
*   starts a rouge like game based on a given data file
*   IN: and integer number of arguments, and an array of strings
*        containing said arguments
*   OUT: 1 if failure,0 if sucess
*   POST: runs a lot of functions, starts ncurses and allows you to
*          play rouge
*   ERROR: if an invalid number of arguments are called the program
*           ends and a message is printed
*          if the computer is out of memory, and player data cannot
*           be allocated, an error message is printed and the program ends
*/
int main(int argc, char * argv[])
{
    //declare largest scope variables (level and player)
    Map * level[6];
    Player * chris;
    Enemy * enemy[20];

    //argument check
    if (argc != 2)
    {
        fprintf(stderr, "Invalid number of arguments. Quitting...\n");
        return(1);
    }



    //load level to memory
    parseDataFile(argv[1], level);

    //allocate player mem and create level
    chris = malloc(sizeof(Player));
    if(chris == NULL)
    {
        fprintf(stderr, "Out of memory. Quitting...\n");
        return(1);
    }
    buildLevel(level, chris, enemy);

    //start game
    playTime(level, chris, enemy);

    //end game if not finished already
    quitGame(chris, level, enemy);

    return(0);

}//end main
