#include "Q4.h"

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree) {
	chessPosList res;
	res.head = NULL;
	res.tail = NULL;
	int longestPath = BOARDSIZE*BOARDSIZE;
	bool flag;

	flag = findLongestRoute(path_tree->root, longestPath, &res);

	if(flag)
		return &res;
	else
		return NULL;
}
bool findLongestRoute(treeNode* root, int counter, chessPosList* res) {
	treeNode* curr;
	chessPosCell* temp;

	if (root == NULL)
		return false;

	if (counter == 1) {

		temp = newNode(root->position);

		res->head = temp;
		res->tail = temp;
		return true;
	}

	else if (isEmptyList(root->next_possible_positions))
		return false;

	else {
		curr = root->next_possible_positions->node;

		while (curr != NULL) {
			if (findLongestRoute(curr, counter - 1, res)) {
				temp = newNode(root->position);
				temp->next = res->head;
				res->head = temp;
				return true;
			}
			curr = root->next_possible_positions->next->node;
		}
		return false;
	}
}
bool isEmptyList(treeNodeListCell *lst) {
	if (lst->node == NULL) {
		return true;
	}
	return false;
}
chessPosCell* newNode(chessPos pos) {
	chessPosCell* temp = (chessPosCell*)malloc(sizeof(chessPosCell));
	checkMemoryAllocation(temp);
	temp->position[0] = pos[0];
	temp->position[1] = pos[1];
	temp->next = NULL;

	return temp;
}