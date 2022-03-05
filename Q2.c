#include "Q2.h"

void display(chessPosList* lst) {
	chessPosCell *curr, *checkSame, *tempPre;
	int size = 0;
	bool pathTable[BOARDSIZE][BOARDSIZE];
	falseTheArr(pathTable, BOARDSIZE);

	if (lst->head == NULL) {
		printf("Empty List\n");
		return;
	}
	else if (lst->head == lst->tail)
		size++;
	else {
		tempPre = lst->head;
		pathTable[tempPre->position[0] - 'A'][tempPre->position[1] - '1'] = true;
		curr = tempPre->next;
		size++;
		while (curr != NULL) {
			if (inList(pathTable, curr)){
				deleteNode(lst, curr, tempPre);
				curr = tempPre->next;
			}
			else {
				size++;
				pathTable[curr->position[0] - 'A'][curr->position[1] - '1'] = true;
				tempPre = curr;
				curr = curr->next;
			}

		}
	}
	printBoard(lst, size);
}
void printBoard(chessPosList* lst, int lstSize) {
	int i, j, h, tempInd = 0;
	chessPosCell* tempPosCell;

	for (h = '0'; h <= COL; h++)
		printf("+---");
	printf("+\n");
	for (h = '0'; h <= COL; h++) {
		if (h == '0') {
			printf("|   ");
			continue;
		}
		printf("| %c ", h);
	}
	printf("|\n");

	tempInd = 1;

	int* movesArr = makeMovesArr(lst);

	for (i = 'A'; i <= ROW; i++) {

		for (h = '0'; h <= COL; h++)
			printf("+---");
		printf("+\n");
		printf("| %c ", i);

		for (j = '1'; j <= COL; j++) {
			if (movesArr[((i - 'A') * BOARDSIZE) + (j - '1')] > 0)
				printf("| %d ", movesArr[((i - 'A') * BOARDSIZE) + (j - '1')]);
			else
				printf("|   ");
		}
		printf("|\n");
	}

	for (h = '0'; h <= COL; h++)
		printf("+---");
	printf("+\n\n");
}
int* makeMovesArr(chessPosList* lst) {
	int numOfMoves = 1;
	int* res = (int*)malloc(sizeof(int) * BOARDSIZE* BOARDSIZE);
	for (int i = 0; i < BOARDSIZE*BOARDSIZE; i++) 
		res[i] = 0;

	chessPosCell* curr = lst->head;
	while (curr != NULL) {
		res[((curr->position[0] - 'A')* BOARDSIZE) + (curr->position[1]-'1')] = numOfMoves;
		numOfMoves++;
		curr = curr->next;
	}
	return res;
}
bool inList(bool pathTable[][BOARDSIZE], chessPos curr) {
	if (pathTable[curr[0] - 'A'][curr[1] - '1'] == true)
		return true;
	else
		return false;
}
void deleteNode(chessPosList* lst, chessPosCell* node, chessPosCell* pnode) {
	if (lst->tail == node) {
		pnode->next = NULL;
		lst->tail = pnode;
		free(node);
	}
	else {
		pnode->next = node->next;
		free(node);
	}
}
void falseTheArr(bool arr[][BOARDSIZE], int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			arr[i][j] = false;
	}
}