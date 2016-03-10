//include
#include "drawMap.h"


void buildLevel(Map * level[6], Player * chris, Enemy * enemy[20])
{
    //declare variables
    int xRef, yRef, i, eneNum;
    int maxX, maxY;

    //allocate enemy memory and set to imaginary
    for(i=0;i<20;i++)
    {
       enemy[i] = malloc(sizeof(Enemy));
       enemy[i]->real = 0;
    }

    //initialize ncurses
    initscr();

    //check if window is big enough, ask to quit if not
    getmaxyx(stdscr, maxY, maxX);

    if (maxX < 96 || maxY < 57)
    {
        char input;
        mvprintw(5, 5, "Error, screen too small, is %d %d, needs to be %d %d, proceed anyway?(y/n) (not recommended)\n", maxY, maxX, 96, 57);
        input = getch();
        if(input == 'n')
        {
            endwin();
            for(i=0;i<6;i++)
            {
                free(level[i]);
            }
            for(i=0;i<20;i++)
            {
                free(enemy[i]);
            }
            free(chris);
            exit(1);
        }
        else
        {
            clear();
        }
    }

    //initalize variables
    xRef=4;
    yRef=4;
    eneNum=0;

    //draw loop
    for (i = 0;i < 6;i++)
    {
        level[i]->refX = xRef;
        level[i]->refY = yRef;
        level[i]->doorNum = 0;
        draw(level, xRef, yRef, i, chris, enemy, &eneNum);

        //set reference location
        xRef += 29;
        if (xRef > 70)
        {
            xRef = 4;
            yRef += 24;
        }

    }//end draw loop

    //draw hallways and border
    drawHalls(level);
    drawBorder();

}

void draw(Map** level, int xPos, int yPos, int room, Player * chris, Enemy * enemy[20], int * eneNum)
{
    //declare variables
    int width, height;

    //intialize variables and srand
    width = level[room]->width;
    height = level[room]->height;
    srand(time(NULL));

    //initailize cursor
    move(yPos, xPos);

    //call subdrawing functions
    drawRoom(&yPos, &xPos, width, height);
    drawElements(level, xPos, yPos, chris, room, width, height, enemy, eneNum);

}//end draw

void drawRoom(int * yPos, int * xPos, int width, int height)
{

    //declare variables
    int i, j;

    //move cursor around in box shape, printing walls
    for (i = 0;i < (width + 2);i++)
    {
        mvaddch(*yPos, *xPos, '-');
        (*xPos)++;
    }
    (*xPos)--;
    for (i = 0;i < (height + 1);i++)
    {
        (*yPos)++;
        mvaddch(*yPos, *xPos ,'|');

    }
    for (i = 0;i < (width + 2);i++)
    {
        mvaddch(*yPos, *xPos, '-');
        (*xPos)--;
    }
    (*xPos)++;
    for (i = 0;i < height;i++)
    {
        (*yPos)--;
        mvaddch(*yPos, *xPos, '|');

    }
    (*xPos)++;

    //fill box interior
    for (i = 0;i < width;i++)
    {
        for (j = 0;j < height;j++)
        {
            mvaddch((*yPos + j), (*xPos + i), '.');
        }
    }

}//end drawRoom


void drawElements(Map * level[6],int  xPos,int  yPos, Player * chris, int room, int width, int height, Enemy * enemy[20], int * eneNum)
{
    //decalre variables
    int xLoc, yLoc, exDigit, i;

    exDigit = 0;
    //create elements
    for (i = 0;i <= level[room]->eleNum;i++)
    {
        //if door
        if (level[room]->elements[i][0] == 'd')
        {
            //draw door
            drawDoor(xPos, yPos, level, room, width, height, i);

        }//end if door

        //any other element
        else
        {
            //parse element location
            yLoc = level[room]->elements[i][1] - '0';

            if((level[room]->elements[i][2] <= '9') &&
               (level[room]->elements[i][2] >= '0'))
            {
                yLoc = ((level[room]->elements[i][1] - '0') * 10) +
                        (level[room]->elements[i][2] - '0');
                exDigit = 1;
            }
            xLoc = level[room]->elements[i][3+exDigit] - '0';

            if((level[room]->elements[i][4 + exDigit] <= '9') &&
               (level[room]->elements[i][4 + exDigit] >= '0'))
            {
                xLoc = ((level[room]->elements[i][3 + exDigit] - '0') * 10)
                      + (level[room]->elements[i][4 + exDigit] - '0');
            }

            //reset variable
            exDigit = 0;

            //hero special case (sets initial hero data)
            if (level[room]->elements[i][0] == 'h')
            {
                createPlayer(level[room]->elements[i], room, chris, level, xLoc, yLoc);
            }
            //print element to screen
            mvaddch((yPos + yLoc), (xPos + xLoc), getFig(level[room]->elements[i][0]));

            //enemy special case (sets enemy data)
            if(level[room]->elements[i][0] == 'm' || level[room]->elements[i][0] == 'M')
            {
                createEnemy(level[room]->elements[i], room, enemy, *eneNum, level, xLoc, yLoc);
                (*eneNum)++;
            }

        }
    }//end element loop

}//end drawElements


void drawDoor(int xPos, int yPos, Map * level[6], int room, int width, int height, int eleNum)
{
    //declare variables
    char wall;
    int loc;

    //find side of room, location and set to unconnected
    wall = level[room]->elements[eleNum][1];
    loc = level[room]->elements[eleNum][2] - '0';
    level[room]->door[level[room]->doorNum].connected = 0;


    //determine wall door is on and add to map and stats
    if (wall == 'n')
    {
        mvaddch((yPos - 1), (xPos + loc), '+');
        level[room]->door[level[room]->doorNum].wall = 'n';
        level[room]->door[level[room]->doorNum].xPos = xPos+loc;
        level[room]->door[level[room]->doorNum].yPos = yPos-1;
    }
    else if (wall == 'e')
    {
        mvaddch((yPos + loc), (xPos + width), '+');
        level[room]->door[level[room]->doorNum].wall = 'e';
        level[room]->door[level[room]->doorNum].xPos = xPos+width;
        level[room]->door[level[room]->doorNum].yPos = yPos+loc;
    }
    else if (wall == 's')
    {
        mvaddch((yPos + height), (xPos + loc), '+');
        level[room]->door[level[room]->doorNum].wall = 's';
        level[room]->door[level[room]->doorNum].xPos = xPos+loc;
        level[room]->door[level[room]->doorNum].yPos = yPos+height;
    }
    else if (wall == 'w')
    {
        mvaddch((yPos + loc), (xPos - 1), '+');
        level[room]->door[level[room]->doorNum].wall = 'w';
        level[room]->door[level[room]->doorNum].xPos = xPos-1;
        level[room]->door[level[room]->doorNum].yPos = yPos+loc;
    }
    //add door to counter
    level[room]->doorNum++;

}//end draw door

void createPlayer(char * info, int room, Player * chris, Map * level[6], int xLoc, int yLoc)
{

    //find and set player position
    chris->xPos = level[room]->refX + xLoc;
    chris->yPos = level[room]->refY + yLoc;

    //set inital room and gold
    chris->room = room;
    chris->gold = 0;
    chris->invNum = 0;
    chris->potNum = 1;
    chris->health = 50;
    chris->att = 5;
    chris->state = '.';
}//end of createPlayer


void createEnemy(char * info, int room, Enemy * enemy[20], int eneNum, Map * level[6], int xLoc, int yLoc)
{
    //declare variable
    char sym;

    //find and set enemy position
    enemy[eneNum]->xPos = level[room]->refX + xLoc+1;
    enemy[eneNum]->yPos = level[room]->refY + yLoc+1;

    //find enemy symbol, set according data to struct
    sym = mvinch(enemy[eneNum]->yPos, enemy[eneNum]->xPos);
    switch (sym)
    {
        case 'A':
            enemy[eneNum]->health = 5;
            enemy[eneNum]->att = 1;
            enemy[eneNum]->spd = 2;
            break;
        case 'B':
            enemy[eneNum]->att = 5;
            enemy[eneNum]->spd = 4;
            enemy[eneNum]->health = 2;
            break;
        case 'S':
            enemy[eneNum]->att = 5;
            enemy[eneNum]->spd = 4;
            enemy[eneNum]->health = 5;
            break;
        case 'Z':
            enemy[eneNum]->att = 5;
            enemy[eneNum]->spd = 2;
            enemy[eneNum]->health = 15;
            break;
        case 'T':
            enemy[eneNum]->att = 5;
            enemy[eneNum]->spd = 3;
            enemy[eneNum]->health = 50;
            break;
    }
    //set enemy to real, assign symbol, and start cycle
    enemy[eneNum]->real = 1;
    enemy[eneNum]->type = sym;
    enemy[eneNum]->cycle = 1;
}//end of createEnemy


char getFig(char sym)
{
    //declare variables
    int random;
    char weakMonsters[4];

    //initalize weak monster array
    weakMonsters[0] = 'A';
    weakMonsters[1] = 'B';
    weakMonsters[2] = 'S';
    weakMonsters[3] = 'Z';
    random = rand() % 4;

    //translate symbol and return
    switch (sym)
    {
        case 'h':
            return('@');
        case 'z':
            return('<');
        case 'a':
            return('>');
        case 'g':
            return('*');
        case 'G':
            return('8');
        case 'w':
            return(')');
        case 'W':
            return('(');
        case 'm':
            return(weakMonsters[random]);
        case 'e':
            return(']');
        case 'M':
            return('T');
        case 'p':
            return('!');
    }
    return(' ');



}//end getFig


void drawBorder()
{
    //draw horizontal lines
    int i;
    for(i = 0;i<91;i++)
    {
        mvaddch(0,i, 'X');
        mvaddch(50,i, 'X');
        mvaddch(57, i, 'X');
    }

    //draw vertical lines
    for(i = 0;i<58;i++)
    {
        mvaddch(i,0, 'X');
        mvaddch(i,90, 'X');
    }

}//end of drawBorder
