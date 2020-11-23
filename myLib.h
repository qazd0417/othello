#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLACK 2
#define WHITE 1
#define BLANK 0
#define MAPSIZE 8

static int dx[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };
static int dy[8] = { 0, 0, -1, 1, -1, 1, -1, 1 };
static int change_list[8][2];


struct Gameboard
{
   int map[MAPSIZE][MAPSIZE];
   int score[3];                     // 0: empty, 1: white, 2: black 
};

void ShowBoard(struct Gameboard *board);
void InitGame(struct Gameboard *board);
void CntStone(struct Gameboard *board);
int PutStone(struct Gameboard *board, int xq, int y, int turn);
int ChangeStone(struct Gameboard *board, int dx, int dy, int x, int y, int color);
