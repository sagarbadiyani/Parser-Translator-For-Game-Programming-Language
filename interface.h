#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Names{
    int count;
    char vars[100][100];
}Names;

typedef struct coordinate{
    int ff;
    int ss;	
}coordinate;

int gameBoard[4][4];
Names names[4][4];

extern coordinate generateRandomIndex();
extern void init();
extern void printGameBoard();
extern void assignName(int x, int y, char *str);
extern void printNames();
extern void action(int direction, int operation);
extern void transpose();
extern void mirrorX();
extern void mirrorY();
extern void rotateMatrix(int direction);
extern void unrotate(int direction);
extern void move(int operation);
extern Names mergeNames(Names a, Names b, int operation);
extern int mergeVal(int a, int b, int operation);
extern void generateTile();
extern void queryTile(int x, int y);
extern void assignVal(int x, int y, int z);
extern void boardState();