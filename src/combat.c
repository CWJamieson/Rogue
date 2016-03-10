
//includes
#include "structs.h"
#include "combat.h"

void combat(int yLoc, int xLoc, Player * chris, Enemy * enemy[20])
{
    //declare variables
    int eneNum, init;
    //allocate memory
    eneNum=0;
    for(eneNum = 0; eneNum < 20 && enemy[eneNum]->real==1;eneNum++)
    {
        if(enemy[eneNum]->xPos == xLoc && enemy[eneNum]->yPos == yLoc)
        {
            break;
        }
    }
    //if no enemy is found (should never happen) default to last
    if(eneNum == 20)
    {
        eneNum = 19;
    }

    //initalize variables
    init = rand() % 10 +1;

    //case 1: you hit enemy: deal damage
    if(init>enemy[eneNum]->spd)
    {
        enemy[eneNum]->health -= chris->att;
        moveText();
        mvprintw(56, 10, "You attack for %d damage!", chris->att);
    }

    //case 2: Enemy hits you: health or attack is lowered
    else
    {
        if(enemy[eneNum]->type == 'A')
        {
            chris->att -= enemy[eneNum]->att;
            moveText();
            mvprintw(56, 10, "You were hit and lost %d attack!", enemy[eneNum]->att);
        }
        else
        {
            chris->health -= enemy[eneNum]->att;
            moveText();
            mvprintw(56, 10, "You were hit and lost %d health!", enemy[eneNum]->att);
        }
    }

}


void moveEnemies(Enemy * enemy[20], Player * chris)
{
    //declare variables
    int i;
    int randMove;

    //cycles through list of enemies
    i=0;
    while(i<20 && enemy[i]->real==1)
    {
        //kill enemy event
        if(enemy[i]->health<1 && enemy[i]->type != '.')
        {
            moveText();
            mvprintw(56, 10, "You killed a %s!", getWord(enemy[i]->type));
            mvaddch(enemy[i]->yPos, enemy[i]->xPos, '.');
            enemy[i]->type = '.';
        }

        //Bat movement cycle: random
        if(enemy[i]->type == 'B')
        {
            randMove = rand() % 2 + 1;
            if(randMove == 1)
            {
                randMove = rand() % 2 +1;
                if(randMove == 1)
                {
                    enemyObjChk(enemy, i, 0, 1, chris);
                }
                else
                {
                    enemyObjChk(enemy, i, 0, -1, chris);
                }
            }
            else
            {
                randMove = rand() %2 + 1;
                if(randMove == 1)
                {
                    enemyObjChk(enemy, i, 1, 0, chris);
                }
                else
                {
                    enemyObjChk(enemy, i, -1, 0, chris);
                }
            }
        }

        //snake movement cycle: side to side
        else if(enemy[i]->type == 'S')
        {
                switch(enemy[i]->cycle)
                {
                    case 1:
                        enemyObjChk(enemy, i, 0, 1, chris);
                        break;
                    case 2:
                        enemyObjChk(enemy, i, 0, 1, chris);
                        break;
                    case 3:
                        enemyObjChk(enemy, i, 0, -1, chris);
                        break;
                    case 4:
                        enemyObjChk(enemy, i, 0, -1, chris);
                        break;
                }

                enemy[i]->cycle++;
                if(enemy[i]->cycle == 5)
                {
                    enemy[i]->cycle = 1;
                }


        }

        //zombie movement cycle: up and down
        else if(enemy[i]->type == 'Z')
        {
            if(enemy[i]->cycle == 1)
            {
                enemyObjChk(enemy, i, 1, 0, chris);
            }
            else
            {
                enemyObjChk(enemy, i, -1, 0, chris);
            }
            enemy[i]->cycle++;
            if(enemy[i]->cycle==3)
            {
                enemy[i]->cycle=1;
            }
        }

        //troll movement patter: circular
        else if(enemy[i]->type == 'T')
        {
                switch(enemy[i]->cycle)
                {
                    case 1:
                        enemyObjChk(enemy, i, 1, 0, chris);
                        break;
                    case 2:
                        enemyObjChk(enemy, i, 0, 1, chris);
                        break;
                    case 3:
                        enemyObjChk(enemy, i, -1, 0, chris);
                        break;
                    case 4:
                        enemyObjChk(enemy, i, 0, -1, chris);
                        break;
                }

                enemy[i]->cycle++;
                if(enemy[i]->cycle == 5)
                {
                    enemy[i]->cycle = 1;
                }

        }
        i++;
    }//end of movement loop
}//end of moveEnemies



void enemyObjChk(Enemy * enemy[20], int eneNum, int yChange, int xChange, Player * chris)
{
    //declare variable
    char newLoc;

    //target location
    newLoc = mvinch(enemy[eneNum]->yPos+yChange, enemy[eneNum]->xPos+xChange);

    //kill event
    if(enemy[eneNum]->health<1 && enemy[eneNum]->type!='.')
    {
        moveText();
        mvprintw(56, 10, "You killed a %s!", getWord(enemy[eneNum]->type));
        enemy[eneNum]->type = '.';
    }

    //case 1: clear: move there
    if(newLoc == '.')
    {
        mvaddch(enemy[eneNum]->yPos, enemy[eneNum]->xPos, '.');
        mvaddch(enemy[eneNum]->yPos + yChange, enemy[eneNum]->xPos +xChange, enemy[eneNum]->type);
        enemy[eneNum]->xPos += xChange;
        enemy[eneNum]->yPos += yChange;
    }

    //case 2: hero: attack
    else if(newLoc == '@')
    {
        combat(enemy[eneNum]->yPos, enemy[eneNum]->xPos, chris, enemy);
    }
    //otherwise creature will not be able to move
}//end of enemyObjChk



char *  getWord(char sym)
{
    //switch block to return name of a monster
    //need I comment further?
    switch(sym)
    {
        case 'A':
            return("Aquator");
        case 'B':
            return("Bat");
        case 'S':
            return("Snake");
        case 'Z':
            return("Zombie");
        case 'T':
            return("Troll");
    }
    return("Unknown Enemy");
}//end of getWord
