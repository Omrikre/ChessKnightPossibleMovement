#ifndef _Q_4
#define _Q_4

#include "Q3.h"

#define CHECK4

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);
bool findLongestRoute(treeNode* root, int counter, chessPosList* res);
bool isEmptyList(treeNodeListCell* lst);
chessPosCell* newNode(chessPos pos);

#endif