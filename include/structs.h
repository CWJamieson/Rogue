#ifndef __CJAMIE04_STRUCTS__
#define __CJAMIE04_STRUCTS__

struct door
{
    char wall;
    int xPos, yPos, connected;
};

typedef struct door Door;


struct map
{
    int width, height, eleNum, refX, refY, doorNum;
    Door door[4];
    char elements[15][6];
};

typedef struct map Map;


struct player
{
    int xPos, yPos, room, gold, invNum, potNum, health, att;
    char state;
    char inv[5][16];
};

typedef struct player Player;

struct enemy
{
    int xPos, yPos, health, real, att, spd, cycle;
    char type;
};

typedef struct enemy Enemy;


#endif
