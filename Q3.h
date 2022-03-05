#ifndef _Q_3
#define _Q_3

#include "Q2.h"

#define CHECK3

typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNode {
	chessPos position;
	treeNodeListCell* next_possible_positions;
}treeNode;

typedef struct _treeNodeListCell {
	treeNode* node;
	struct _treeNodeListCell* next;
}treeNodeListCell;

typedef struct _pathTree {
	treeNode* root;
}pathTree;



pathTree findAllPossibleKnightPaths(chessPos* startingPosision);
treeNode* findAllPossibleKnightPathsRec(chessPosArray*** chessLst, chessPos* root, bool pathTable[][BOARDSIZE]);
void deleteTail(chessPosList* hLst);
bool isEmpty(chessPosList* lst);
chessPosList* makeEmptyCPL();
chessPosList* makeMovesLst(chessPosArray* array, bool pathTable[][BOARDSIZE]);
void insertNode(chessPos* pos, chessPosList* lst);
void freeCPL(chessPosList* lst);


#endif