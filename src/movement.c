#include "structs.h"
#include "movement.h"


int actionReader(Player * chris, Map ** level, int * refX, int * refY, int * width, int * height, int xChange, int yChange, Enemy * enemy[20])
{
    //checks for obsticle
    if (objectCheck(chris, level, xChange, yChange, refX, refY, width, height, enemy))
    {
        //if cannot move
        return(1);
    }
    //checks all sides and tries to move
    movePlayer(chris, xChange, yChange);
    return 0;
}//end actionReader



int objectCheck(Player * chris, Map * level[6], int checkX, int checkY, int * refX, int * refY, int * width, int * height, Enemy * enemy[20])
{
    //decalre variables
    int randGold;
    int printY;
    srand(time(NULL));

    //initialize printY
    printY = 56;

    //clear the status line
    move(printY, 10);
    //check location switch block
    switch (mvinch((chris->yPos + 1 + checkY), (chris->xPos + 1 + checkX)))
    {
        //add gold
        case '*':
            randGold = rand() % 51;
            moveText();
            mvprintw(printY, 10, "You picked up %d gold", randGold);
            chris->gold += randGold;
            break;

        case '8':
            randGold = rand() % 201 + 50;
            moveText();
            mvprintw(printY, 10, "You picked up %d gold", randGold);
            chris->gold+= randGold;

            break;

        //end game
        case '>':
        case '<':
            quitGame(chris, level, enemy);

        //pick up mostly useless items
        case ')':
            if(chris->invNum!=5)
            {
                moveText();
                mvprintw(printY, 10, "You picked up a common weapon!");
                strcpy(chris->inv[chris->invNum], "common weapon +");
                chris->invNum++;
            }
            else
            {
                moveText();
                mvprintw(printY, 10, "You broke a common weapon!");
            }

            break;
        case '(':
            if(chris->invNum!=5)
            {
                moveText();
                mvprintw(printY, 10, "You picked up a rare weapon!");
                strcpy(chris->inv[chris->invNum], "rare weapon +");
                chris->invNum++;
            }
            else
            {
                moveText();
                mvprintw(printY, 10, "You broke a rare weapon!");
            }

            break;
        case ']':
            if(chris->invNum!=5)
            {
                moveText();
                mvprintw(printY, 10, "You picked up equipment!");
                strcpy(chris->inv[chris->invNum], "equipment +");
                chris->invNum++;
            }
            else
            {
                moveText();
                mvprintw(printY, 10, "You broke equipment!");
            }

            break;
        case '!':
            moveText();
            mvprintw(printY, 10, "You picked up a health potion!");
            chris->potNum++;
            break;

        //start combat if monster is stepped on
        case 'A':
        case 'B':
        case 'S':
        case 'Z':
        case 'T':
            combat((chris->yPos + 1 + checkY), (chris->xPos + 1 + checkX), chris, enemy);
            return(1);

        //border and wall collision
        case '|':
        case '-':
        case ' ':
        case 'X':
            moveText();
            mvprintw(printY, 10, "You bump your nose.");
            return(1);

        //door collision
        case '+':
            moveText();
            mvprintw(printY, 10, "You pass throgh the portal.");
            break;
    }
    //reset cursor and return
    move(printY, 10);
    return(0);

}//end objectCheck


void movePlayer(Player * chris, int xChange, int yChange)
{
    char state;
    //replace player with state ('.', '+', or '#')
    mvaddch((chris->yPos + 1), (chris->xPos + 1), chris->state);
    chris->xPos += xChange;
    chris->yPos += yChange;

    //set new state
    state = mvinch(chris->yPos + 1, chris->xPos +1);
    if(state != '+' && state != '#')
    {
        state = '.';
    }
    chris->state=state;

    //add player to new location
    mvaddch((chris->yPos + 1), (chris->xPos + 1), '@');

}//end movePlayer
