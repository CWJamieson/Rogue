//includes
#include "structs.h"
#include "parseLevel.h" 


void parseDataFile(char * path, Map * level[6])
{
    //declare variables (and allocate memory)
    FILE* data;
    char line[256];
    char tmp[10];
    int i, p, j;
    for (i = 0;i < 6;i++)
    {
        level[i] = malloc(sizeof(Map));
        if(level[i] == NULL)
        {
            fprintf(stderr, "Out of memory. Quitting...\n");
            exit(1);
        }
    }

    //initalize variables
    p = 0;
    j = 0;
    i = 0;
    data = fopen(path, "r");
    if (data == NULL)
    {
        printf("File not found. Quitting...\n");
        exit(1);
    }
    
    
    //start parse loop (handles whole room)
    while (fgets(line, 256, data) != NULL)
    {
        //declare vairable
        int eleNum;

        //reset variables
        p = 0;
        j = 0;
        eleNum = 0;
        
        //read in room dimentions
        while (line[j] != ' ')
        {
            tmp[p] = line[j];
            if (tmp[p] == 'X')
            {
                tmp[p] = '\0';
                p = 0;
                level[i]->height = atoi(tmp);

            }
            else
            {
                p++;
            }
            j++;


        }
        tmp[p] = '\0';
        p = 0;
        level[i]->width = atoi(tmp);
        
        //skip space
        j++;


        //start parse element loop (handles invidual characters)
        while (line[j] != '\n')
        {
            tmp[p] = line[j];
            
            //adds element to level
            if (tmp[p] == ' ')
            {
                tmp[p] = '\0';
                p = 0;
                strcpy(level[i]->elements[eleNum], tmp);
                eleNum++;
            }
            else
            {
                p++;
            }

            j++;
        }//end element loop
        
        //set last element
        tmp[p] = '\0';
        strcpy(level[i]->elements[eleNum], tmp);

        //set number of elements
        level[i]->eleNum = eleNum;

        i++;
    }//end of parse loop
    
    fclose(data);

}//end parseDataFile
