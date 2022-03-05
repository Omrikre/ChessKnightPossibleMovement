#ifndef _Q_2
#define _Q_2

#include "Q1.h"

#define CHECK2

typedef struct _chessPosCell {
	chessPos position;
	struct _chessPosCell* next;
} chessPosCell;

typedef struct _chessPosList {
	chessPosCell* head;
	chessPosCell* tail;
} chessPosList;


void display(chessPosList* lst);
void printBoard(chessPosList* lst, int lstSize);
void deleteNode(chessPosList* lst, chessPosCell* node, chessPosCell* pnode);
int* makeMovesArr(chessPosList* lst);
bool inList(bool pathTable[][BOARDSIZE], chessPos curr);
void falseTheArr(bool arr[][BOARDSIZE], int size);


#endif