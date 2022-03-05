#include "Q3.h"

pathTree findAllPossibleKnightPaths(chessPos* startingPosision) {
	chessPosArray*** possibleMoves = validKnightMoves();
	pathTree res;
	bool pathTable[BOARDSIZE][BOARDSIZE];
	falseTheArr(pathTable, BOARDSIZE);

	res.root = findAllPossibleKnightPathsRec(possibleMoves, startingPosision, pathTable);

	return res;
}



treeNode* findAllPossibleKnightPathsRec(chessPosArray*** chessLst, chessPos* root, bool pathTable[][BOARDSIZE]) {

	chessPosList* movesLst;
	chessPosCell* curr;

	treeNode* newNode = (treeNode*)malloc(sizeof(treeNode));
	checkMemoryAllocation(newNode);
	treeNodeListCell* nextPos = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	checkMemoryAllocation(nextPos);

	newNode->position[0] = root[0][0];
	newNode->position[1] = root[0][1];

	pathTable[(root[0][0] - 'A')][(root[0][1] - '1')] = true;

#ifdef CHECK3
	printf("\n%c%c -->  ", root[0][0], root[0][1]);
#endif

	chessPosArray* array = chessLst[root[0][0] - 'A'][root[0][1] - '1'];
	movesLst = makeMovesLst(array, pathTable);

	if (!isEmpty(movesLst)) {
		curr = movesLst->head;
		
		while (curr != NULL) {
			newNode->next_possible_positions = findAllPossibleKnightPathsRec(chessLst, curr->position, pathTable);
			curr = curr->next;
		}
		pathTable[(*root[0] - 'A')][(*root[1] - '1')] = false;
	}
	else {
		newNode->next_possible_positions = NULL;
		pathTable[(*root[0] - 'A')][(*root[1] - '1')] = false;
	}


	return newNode;
}




bool isEmpty(chessPosList* lst) {
	if (lst->head == NULL)
		return true;
	return false;
}
chessPosList* makeEmptyCPL() {
	chessPosList *lst = (chessPosList*)malloc(sizeof(chessPosList));
	checkMemoryAllocation(lst);

	lst->head = NULL;
	lst->tail = NULL;
	return lst;
}
chessPosList* makeMovesLst(chessPosArray *array, bool pathTable[][BOARDSIZE]) {
	chessPos* curr;
	chessPosList* cpl = makeEmptyCPL();
	if (array == NULL)
		return cpl;

	for (int i = 0; i < array->size; i++) {
		curr = array->positions[i];
		if (!inList(pathTable, curr))
			insertNode(curr, cpl);
#ifdef CHECK3
		printf("%c%c, ", curr[0][0], curr[0][1]);
#endif
	}

	return cpl;
}
void insertNode(chessPos* pos, chessPosList* lst) {
	chessPosCell* temp = (chessPosCell*)malloc(sizeof(chessPosCell));
	checkMemoryAllocation(temp);

	temp->next = NULL;
	temp->position[0] = pos[0][0];
	temp->position[1] = pos[0][1];

	if (lst->head == NULL) {
		lst->head = temp;
		lst->tail = temp;
	}

	else {
		lst->tail->next = temp;
		lst->tail = temp;
	}

}




void deleteTail(chessPosList* hLst) {
	if (hLst->head == NULL)
		return;

	chessPosCell* curr = hLst->head;

	if (curr->next == NULL) {
		free(curr);
		hLst->head = hLst->tail = NULL;
		return;
	}
	while (curr->next->next != NULL)
		curr = curr->next;


	free(curr->next);
	curr->next = NULL;
	hLst->tail = curr;
}

