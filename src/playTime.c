//includes
#include "structs.h"
#include "playTime.h"

//start playTime
void playTime(Map * level[6], Player * chris, Enemy * enemy[20])
{

    //declare variables
    int width, height;
    int refX, refY;

    //intialize variables
    refX = level[chris->room]->refX;
    refY = level[chris->room]->refY;
    height = level[chris->room]->height;
    width = level[chris->room]->width;

    //disable typing to screen
    noecho();

    //start play-time loop
    while (1)
    {
        char action;
        //print status bar
        mvprintw(51, 20, "Health: %d, Potions: %d, Attack: %d, Inv: %d/5, Gold: %d", chris->health, chris->potNum, chris->att, chris->invNum, chris->gold);

        //check if dead, quit if true
        if(chris->health < 1)
        {
            quitGame(chris, level, enemy);
        }

        //reset cursor
        move((60), 5);

        //get action
        action = getch();

        //checks direction key pressed (if incorrect will skip to next action)
        if (action == 'w')
        {
            actionReader(chris, level, &refX, &refY, &width, &height, 0, -1, enemy);
        }
        else if (action == 's')
        {
            actionReader(chris, level, &refX, &refY, &width, &height, 0, 1, enemy);
        }
        else if (action == 'a')
        {
            actionReader(chris, level, &refX, &refY, &width, &height, -1, 0, enemy);
        }
        else if (action == 'd')
        {
            actionReader(chris, level, &refX, &refY, &width, &height, 1, 0, enemy);
        }
        //use potion event
        else if (action == 'p')
        {
            usePotion(chris);
        }
        //if player quits
        else if (action == 'q')
        {
            quitGame(chris, level, enemy);
        }
        moveEnemies(enemy, chris);


    }//end play-time loop


}//end playTIme


void usePotion(Player * chris)
{
    //declare/initialize variable
    int printY;
    printY = 56;


    move(printY, 10);
    //case 1: out of potions: print error message
    if(chris->potNum == 0)
    {
        moveText();
        mvprintw(printY, 10, "Out of potions.");
    }

    //case 2: use a potion: heals player and lowers amount of potions
    else
    {
        chris->potNum--;
        chris->health = 50;
        moveText();
        mvprintw(printY, 10, "Hero recovered full health.");
    }
}//end of usePotion

void quitGame(Player * chris, Map * level[6], Enemy * enemy[20])
{
    //declare variables
    int i;
    int randStat;

    //clear screen and print end messages
    erase();
    mvprintw(10, 10, "You collected %d gold.", chris->gold);
    mvprintw(11, 10, "You still have %d potion(s).", chris->potNum);
    //print inventory
    mvprintw(12, 10, "Inventory:");
    for(i = 0;i< chris->invNum;i++)
    {
        if(chris->inv[i][0]=='c')
        {
            randStat = rand() % 9 + 1;
        }
        else if(chris->inv[i][0]=='r')
        {
            randStat = rand() % 6 +10;
        }
        else
        {
            randStat = rand() % 21;
        }
        mvprintw(13+i, 10, "%s%d", chris->inv[i], randStat);
    }
    if(chris->invNum==0)
    {
        mvprintw(13, 10, "<empty>");
    }
    mvprintw(20, 10, "Press any key to quit. Thanks for playing!");
    move(21, 10);

    //wait for quit prompt
    getch();

    //free memory
    for (i = 0;i < 6;i++)
    {
        free(level[i]);
    }
    for(i=0;i<20;i++)
    {
        free(enemy[i]);
    }
    free(chris);

    //close ncurses and exit
    endwin();
    exit(0);

}//end quitGame


void moveText()
{
    //declare variables
    int i, j;
    char sym;

    //moveText loop
    for(i = 0;i<5;i++)
    {
        for(j=1;j<90;j++)
        {
            //move each character up 1
            sym = mvinch(53+i, j);
            mvaddch(52+i, j, sym);
        }
    }
    //clear bottom row
    for(i = 1; i<90;i++)
    {
        mvaddch(56, i, ' ');
    }
}//end of moveText
