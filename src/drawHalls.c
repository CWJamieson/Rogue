
//includes
#include "drawHalls.h"

void drawHalls(Map * level[6])
{
    //declare variables
    int xPos, yPos, i, j, yVal;

    //level loop
    for(i=0;i<6;i++)
    {
        //sets inital hallway point
        xPos = level[i]->door[0].xPos;
        yPos = level[i]->door[0].yPos;
        
        //doesnt need to check on last iteration
        if(i != 5)
        {
            //if theres only 1 door, connect both hallways to that door
            if(level[i+1]->doorNum == 1)
            {
                level[i+1]->door[1].xPos = level[i+1]->door[0].xPos;
                level[i+1]->door[1].yPos = level[i+1]->door[0].yPos;
                level[i+1]->door[1].wall = level[i+1]->door[0].wall;
                level[i+1]->door[1].connected = 0;
            }
        }
        //to connect hallways horizontally
        if(i!=2 && i!= 5)
        {
            //General Format shown on case n applies to all 4 cases
            //case 1: start wall is north
            if(level[i]->door[0].wall=='n')
            {
                //bring wall out of level cubical
                drawHall(xPos, yPos-1, xPos, yPos-2);

                //if else structure to get to desired wall of next room
                if(level[i+1]->door[1].wall=='n')
                {
                    drawHall(xPos, yPos-2, level[i+1]->door[1].xPos, yPos-2);
                    drawHall(level[i+1]->door[1].xPos, yPos-2, level[i+1]->door[1].xPos, level[i+1]->door[1].yPos-1);

                }
                else if(level[i+1]->door[1].wall=='e')
                {
                    drawHall(xPos, yPos-2, (xPos/29)*29+29+27, yPos-2);
                    drawHall((xPos/29)*29+29+27, yPos-2, (xPos/29)*29+29+27, level[i+1]->door[1].yPos);
                    drawHall((xPos/29)*29+29+27, level[i+1]->door[1].yPos, level[i+1]->door[1].xPos+1, level[i+1]->door[1].yPos);

                }
                else if(level[i+1]->door[1].wall=='w')
                {
                    drawHall(xPos, yPos-2, (xPos/29)*29+27, yPos-2);
                    drawHall((xPos/29)*29+27, yPos-2, (xPos/29)*29+27, level[i+1]->door[1].yPos);
                    drawHall((xPos/29)*29+27, level[i+1]->door[1].yPos, level[i+1]->door[1].xPos-1, level[i+1]->door[1].yPos);

                }
                else if(level[i+1]->door[1].wall=='s')
                {
                    drawHall(xPos, yPos-2, (xPos/29)*29+27, yPos-2);
                    drawHall((xPos/29)*29+27, yPos-2, (xPos/29)*29+27, yPos+22);
                    drawHall((xPos/29)*29+27, yPos+22, level[i+1]->door[1].xPos, yPos+22);
                    drawHall(level[i+1]->door[1].xPos, yPos+22, level[i+1]->door[1].xPos, level[i+1]->door[1].yPos+1);

                }
                //mark both doors as connected
                level[i]->door[0].connected=1;
                level[i+1]->door[1].connected=1;

            }
            //case 2: initial wall is east
            else if(level[i]->door[0].wall=='e')
            {
                //free from cubical
                drawHall(xPos+1, yPos, xPos+(23-level[i]->width)+2, yPos);

                //if else structure to get to desired wall
                if(level[i+1]->door[1].wall=='n')
                {
                    drawHall(xPos+(23-level[i]->width)+2, yPos, xPos+(23-level[i]->width)+2, (yPos/24)*24+1);
                    drawHall(xPos+(23-level[i]->width)+2, (yPos/24)*24+1, level[i+1]->door[1].xPos, (yPos/24)*24+1);
                    drawHall(level[i+1]->door[1].xPos, (yPos/24)*24+1, level[i+1]->door[1].xPos, level[i+1]->door[1].yPos-1);

                }
                else if(level[i+1]->door[1].wall=='e')
                {
                    drawHall(xPos+(23-level[i]->width)+2, yPos, xPos+(23-level[i]->width)+2, (yPos/24)*24+1);
                    drawHall(xPos+(23-level[i]->width)+2, (yPos/24)*24+1, level[i+1]->door[1].xPos+2, (yPos/24)*24+1);
                    drawHall(level[i+1]->door[1].xPos+2, (yPos/24)*24+1, level[i+1]->door[1].xPos+2, level[i+1]->door[1].yPos);
                    drawHall(level[i+1]->door[1].xPos+2, level[i+1]->door[1].yPos, level[i+1]->door[1].xPos+1, level[i+1]->door[1].yPos);

                }
                else if(level[i+1]->door[1].wall=='w')
                {
                    drawHall(xPos+(23-level[i]->width)+2, yPos, xPos+(23-level[i]->width)+2, level[i+1]->door[1].yPos);
                    drawHall(xPos+(23-level[i]->width)+2, level[i+1]->door[1].yPos, level[i+1]->door[1].xPos-1, level[i+1]->door[1].yPos);

                }
                else if(level[i+1]->door[1].wall=='s')
                {

                    drawHall(xPos+(23-level[i]->width)+2, yPos, xPos+(23-level[i]->width)+2, (yPos/24)*24+24+1);
                    drawHall(xPos+(23-level[i]->width)+2, (yPos/24)*24+24+1, level[i+1]->door[1].xPos, (yPos/24)*24+24+1);
                    drawHall(level[i+1]->door[1].xPos, (yPos/24)*24+24+1, level[i+1]->door[1].xPos, level[i+1]->door[1].yPos+1);

                }

                //mark doors as connected
                level[i]->door[0].connected=1;
                level[i+1]->door[1].connected=1;
            }

            //case 3: initial wall is west
            else if(level[i]->door[0].wall=='w')
            {
                //free from cubical
                drawHall(xPos-1, yPos, xPos-2, yPos);

                //if else structure to get to desired wall
                if(level[i+1]->door[1].wall=='n')
                {
                    drawHall(xPos-2, yPos, xPos-2, (yPos/24)*24+1);
                    drawHall(xPos-2, (yPos/24)*24+1, level[i+1]->door[1].xPos, (yPos/24)*24+1);
                    drawHall(level[i+1]->door[1].xPos, (yPos/24)*24+1, level[i+1]->door[1].xPos, level[i+1]->door[1].yPos-1);

                }
                else if(level[i+1]->door[1].wall=='e')
                {
                    drawHall(xPos-2, yPos, xPos-2, (yPos/24)*24+1);
                    drawHall(xPos-2, (yPos/24)*24+1, level[i+1]->door[1].xPos+2, (yPos/24)*24+1);
                    drawHall(level[i+1]->door[1].xPos+2, (yPos/24)*24+1, level[i+1]->door[1].xPos+2, level[i+1]->door[1].yPos);
                    drawHall(level[i+1]->door[1].xPos+2, level[i+1]->door[1].yPos, level[i+1]->door[1].xPos+1, level[i+1]->door[1].yPos);

                }
                else if(level[i+1]->door[1].wall=='w')
                {
                    drawHall(xPos-2, yPos, xPos-2, (yPos/24)*24+24+1);
                    drawHall(xPos-2, (yPos/24)*24+24+1, level[i+1]->door[1].xPos-2, (yPos/24)*24+24+1);
                    drawHall(level[i+1]->door[1].xPos-2, (yPos/24)*24+24+1, level[i+1]->door[1].xPos-2, level[i+1]->door[1].yPos);
                    drawHall(level[i+1]->door[1].xPos-2, level[i+1]->door[1].yPos, level[i+1]->door[1].xPos-1, level[i+1]->door[1].yPos);

                }
                else if(level[i+1]->door[1].wall=='s')
                {

                    drawHall(xPos-2, yPos, xPos-2, (yPos/24)*24+24+2);
                    drawHall(xPos-2, (yPos/24)*24+24+2, level[i+1]->door[1].xPos, (yPos/24)*24+24+2);
                    drawHall(level[i+1]->door[1].xPos, (yPos/24)*24+24+2, level[i+1]->door[1].xPos, level[i+1]->door[1].yPos+1);

                }

                //mark doors as connected
                level[i]->door[0].connected=1;
                level[i+1]->door[1].connected=1;
            }

            //case 4: initial wall is south
            else if(level[i]->door[0].wall=='s')
            {

                //if else structure to get from initial wall to destination
                if(level[i+1]->door[1].wall=='n')
                {
                    drawHall(xPos, yPos+1, xPos, yPos+(20-level[i]->height)+2);
                    drawHall(xPos, yPos+(20-level[i]->height)+2, (xPos/29)*29+29+2, yPos+(20-level[i]->height)+2);
                    drawHall((xPos/29)*29+29+2, yPos+(20-level[i]->height)+2, (xPos/29)*29+29+2, level[i+1]->door[1].yPos-2);
                    drawHall((xPos/29)*29+29+2, level[i+1]->door[1].yPos-2, level[i+1]->door[1].xPos, level[i+1]->door[1].yPos-2);
                    drawHall(level[i+1]->door[1].xPos, level[i+1]->door[1].yPos-2, level[i+1]->door[1].xPos, level[i+1]->door[1].yPos-1);

                }
                else if(level[i+1]->door[1].wall=='e')
                {
                    drawHall(xPos, yPos+1, xPos, yPos+(20-level[i]->height)+2);
                    drawHall(xPos, yPos+(20-level[i]->height)+2, level[i+1]->door[1].xPos+2, yPos+(20-level[i]->height)+2);
                    drawHall(level[i+1]->door[1].xPos+2, yPos+(20-level[i]->height)+2, level[i+1]->door[1].xPos+2, level[i+1]->door[1].yPos);
                    drawHall(level[i+1]->door[1].xPos+2, level[i+1]->door[1].yPos, level[i+1]->door[1].xPos+1, level[i+1]->door[1].yPos);

                }
                else if(level[i+1]->door[1].wall=='w')
                {
                    drawHall(xPos, yPos+1, xPos, yPos+(20-level[i]->height)+2);
                    drawHall(xPos, yPos+(20-level[i]->height)+2, level[i+1]->door[1].xPos-2, yPos+(20-level[i]->height)+2);
                    drawHall(level[i+1]->door[1].xPos-2, yPos+(20-level[i]->height)+2, level[i+1]->door[1].xPos-2, level[i+1]->door[1].yPos);
                    drawHall(level[i+1]->door[1].xPos-2, level[i+1]->door[1].yPos, level[i+1]->door[1].xPos-1, level[i+1]->door[1].yPos);

                }
                else if(level[i+1]->door[1].wall=='s')
                {
                    if(level[i+1]->height>level[i]->height)
                    {
                        yVal = level[i+1]->door[1].yPos+2;
                    }
                    else
                    {
                        yVal = level[i]->door[0].yPos+2;
                    }
                    drawHall(xPos, yPos+1, xPos, yVal);
                    drawHall(xPos, yVal, level[i+1]->door[1].xPos, yVal);
                    drawHall(level[i+1]->door[1].xPos, yVal, level[i+1]->door[1].xPos, level[i+1]->door[1].yPos+1);

                }

                //mark doors as connected
                level[i]->door[0].connected=1;
                level[i+1]->door[1].connected=1;
            }
        }//end of horizontal connecting hallways

        //right side vertical connection
        else if(i==2)
        {
            //if else structure to go from any wall to the junction at point (25, 59)
            if(level[i]->door[0].wall == 'n')
            {
                drawHall(level[i]->door[0].xPos, level[i]->door[0].yPos-1, level[i]->door[0].xPos, level[i]->door[0].yPos-2);
                drawHall(level[i]->door[0].xPos, level[i]->door[0].yPos-2, 59, level[i]->door[0].yPos-2);
                drawHall(59, level[i]->door[0].yPos-2, 59, 25);
            }
            else if(level[i]->door[0].wall == 'e')
            {
                drawHall(level[i]->door[0].xPos+1, level[i]->door[0].yPos, level[i]->door[0].xPos+2, level[i]->door[0].yPos);
                drawHall(level[i]->door[0].xPos+2, level[i]->door[0].yPos, level[i]->door[0].xPos+2, 25);
                drawHall(level[i]->door[0].xPos+2, 25, 59, 25);
            }
            else if(level[i]->door[0].wall == 's')
            {
                drawHall(level[i]->door[0].xPos, level[i]->door[0].yPos+1, level[i]->door[0].xPos, 25);
                drawHall(level[i]->door[0].xPos, 25, 59, 25);
            }
            else if(level[i]->door[0].wall == 'w')
            {
                drawHall(level[i]->door[0].xPos-1, level[i]->door[0].yPos, 59, level[i]->door[0].yPos);
                drawHall(59, level[i]->door[0].yPos, 59, 25);

            }


            //if else structure to get from the junction to any wall on the destination room
            if(level[5]->door[0].wall == 'n')
            {
                drawHall(59, 25, level[5]->door[0].xPos, 25);
                drawHall(level[5]->door[0].xPos, 25, level[5]->door[0].xPos, 27);
            }
            else if(level[5]->door[0].wall == 'e')
            {
                drawHall(59, 25, 88, 25);
                drawHall(88, 25, 88, level[5]->door[0].yPos);
                drawHall(88, level[5]->door[0].yPos, level[5]->door[0].xPos+1, level[5]->door[0].yPos);

            }
            else if(level[5]->door[0].wall == 's')
            {
                drawHall(59, 25, 59, 49);
                drawHall(59, 49, level[5]->door[0].xPos, 49);
                drawHall(level[5]->door[0].xPos, 49, level[5]->door[0].xPos, level[5]->door[0].yPos+1);

            }
            else if(level[5]->door[0].wall == 'w')
            {
                drawHall(59, 25, 59, level[5]->door[0].yPos);
                drawHall(59, level[5]->door[0].yPos, 60, level[5]->door[0].yPos);

            }

            //mark doors as connected
            level[i]->door[0].connected=1;
            level[5]->door[0].connected=1;
        }//end of right side vertical case


        //extra doors
        for(j=0;j< level[i]->doorNum;j++)
        {
            if(level[i]->door[j].connected==0)
            {
                //create hallways leading to points corners just outside room
                if(level[i]->door[j].wall=='n')
                {
                    drawHall(level[i]->door[j].xPos, level[i]->door[j].yPos-1, level[i]->door[j].xPos, level[i]->door[j].yPos-2);
                    drawHall(level[i]->door[j].xPos, level[i]->door[j].yPos-2, (level[i]->door[j].xPos/29)*29+1, level[i]->door[j].yPos-2);
                }
                else if(level[i]->door[j].wall=='e')
                {
                    drawHall(level[i]->door[j].xPos+1, level[i]->door[j].yPos, level[i]->door[j].xPos+2, level[i]->door[j].yPos);
                    drawHall(level[i]->door[j].xPos+2, level[i]->door[j].yPos, level[i]->door[j].xPos+2, (level[i]->door[j].yPos/24)*24+25);

                }
                else if(level[i]->door[j].wall=='s')
                {
                    drawHall(level[i]->door[j].xPos, level[i]->door[j].yPos+1, level[i]->door[j].xPos, level[i]->door[j].yPos+2);
                    drawHall(level[i]->door[j].xPos, level[i]->door[j].yPos+2, (level[i]->door[j].xPos/29)*29+30, level[i]->door[j].yPos+2);

                }
                else if(level[i]->door[j].wall=='w')
                {
                    drawHall(level[i]->door[j].xPos-1, level[i]->door[j].yPos, level[i]->door[j].xPos-2, level[i]->door[j].yPos);
                    drawHall(level[i]->door[j].xPos-2, level[i]->door[j].yPos, level[i]->door[j].xPos-2, (level[i]->door[j].yPos/24)*24+1);

                }
            }
        }//end of extra doors
    }//end of level loop

    //declare variable
    int count;

    //Left side connection
    //loop to find connection point between rooms 1 & 2
    count=0;
    for(j=24;j>1;j--)
    {
        for(i=28;i<32;i++)
        {
            //connection point found
            if((char)mvinch(j, i) == '#')
            {
                count++;
                xPos = i;
                yPos = j;
            }
            if(count!=0)
            {
                break;
            }
        }
            if(count!=0)
            {
                break;
            }

    }//end of connection loop

    //loop to build hallway to room 3 & 4 connection
    while((char)mvinch(yPos+1, xPos) != '#' && yPos<52)
    {
        yPos++;
        mvaddch(yPos, xPos, '#');
    }

}//end of drawHalls

void drawHall(int xi, int yi, int xf, int yf)
{
    //declare variables
    int i;
    //case 1: horizontal halls
    if(xi!=xf)
    {
        //swap to make destination value bigger
        if(xi>xf)
        {
            xi+=xf;
            xf=xi-xf;
            xi=xi-xf;
        }

        //draw hall
        for(i=xi;i<=xf;i++)
        {
            mvaddch(yi, i, '#');
        }
    }//end of case 1

    //case 2: vertical halls
    else
    {
        //swap to make destination bigger
        if(yi>yf)
        {
            yi+=yf;
            yf=yi-yf;
            yi=yi-yf;
        }

        //draw hall
        for(i=yi;i<=yf;i++)
        {
            mvaddch(i, xi, '#');
        }
    }//end of case 1
}//end of drawHall
