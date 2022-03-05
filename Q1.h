#ifndef _Q_1
#define _Q_1


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ROW 'D'
#define COL '4'
#define BOARDSIZE 4

typedef char chessPos[2];

typedef struct _chessPosArray {
	unsigned int size;
	chessPos* positions;
} chessPosArray;

chessPosArray*** validKnightMoves();
void checkMemoryAllocation(void* address);

#endif