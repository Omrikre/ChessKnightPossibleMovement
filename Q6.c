#include "Q6.h"

int checkAndDisplayPathFromeFile(char* file_name) {

	FILE* fb = fopen(file_name, "rb");
	checkFileIsOpen(fb, file_name);
	if (fb == NULL)
		return -1;
	chessPosList* lst;
	short numOfPos;

	// get the list from the bin file
	fread(&numOfPos, sizeof(short), 1, fb);
	lst = getPosFromBinFile(numOfPos, fb);
	
	fclose(fb);                             

	if (!checkValidPath(lst))
		return 1;

	numOfPos -= checkIfDup(lst);
	
	printBoard(lst, numOfPos);

	freeCPL(lst);

	if (numOfPos == BOARDSIZE*BOARDSIZE)
		return 2;
	else
		return 3;
}
bool checkValidPath(chessPosList* lst) {
	chessPosArray*** movesLst = validKnightMoves();
	chessPosCell* curr = lst->head;

	while (curr != NULL) {
		if (!inThePositionArr(curr->position, movesLst[curr->position[0] - 'A'][curr->position[1] - '1']))
			return false;
		curr = curr->next;
	}
	return true;
}
bool inThePositionArr(chessPos checkPos, chessPosArray* curr) {
	int size = curr->size;
	for (int i = 0; i < size; i++) {
		if ((checkPos[0] == curr->positions[i][0]) && (checkPos[1] == curr->positions[i][1]))
			return true;
	}
	return false;
}
int checkIfDup(chessPosList* lst) {
	chessPosCell* curr, * checkSame, * tempPre;
	curr = lst->head;
	int counter = 0;

	if (lst->head == NULL) {
		printf("Empty List\n");
		return counter;
	}
	while (curr != lst->tail && curr != NULL) {
		tempPre = curr;
		checkSame = curr->next;

		while (checkSame != NULL) {
			if ((curr->position[0] == checkSame->position[0]) && (curr->position[1] == checkSame->position[1])) {

				deleteNode(lst, checkSame, tempPre);
				checkSame = tempPre->next;
				counter++;
				continue;
			}
			tempPre = checkSame;
			checkSame = checkSame->next;
		}
		curr = curr->next;
	}
	return counter;
}
chessPosList* getPosFromBinFile(int size, FILE* fName) {
	BYTE temp[3];
	chessPosList* lst = (chessPosList*)malloc(sizeof(chessPosList));
	checkMemoryAllocation(lst);
	chessPos posArr[4];
	lst->head = lst->tail = NULL;

	for (int i = 0; i < size/4; i++) {
		fread(temp, sizeof(BYTE), 3, fName);
		getDecodedData(temp, posArr, 4);
		for (int j = 0; j < 4; j++) 
			insertNode((posArr+j), lst);
	}

	int numOfOddments = size % 4;
	if (numOfOddments == 0)
		return lst;
	
	chessPos* oddmentsPos = (chessPos*)malloc(sizeof(chessPos) * numOfOddments);
	checkMemoryAllocation(oddmentsPos);
	fread(temp, sizeof(BYTE), numOfOddments, fName);
	getDecodedData(temp, posArr, numOfOddments);

	for (int i = 0; i < numOfOddments; i++)
		insertNode((posArr+i), lst);

	free(oddmentsPos);

	return lst;
}
void getDecodedData(BYTE* data, chessPos* decData, int numOfChar) {
	BYTE mask1 = 0xE0;	//11100000  byte 1 (most significant byte - the left most one)
	BYTE mask2 = 0x1C;	//00011100  byte 1
	BYTE mask3a = 0x03, mask3b = 0x80;	//0000001110000000 bytes 1+2 
	BYTE mask4 = 0x70;	//01110000  byte 2
	BYTE mask5 = 0x0E;	//00001110  byte 2
	BYTE mask6a = 0x01, mask6b = 0xC0;	//0000000111000000 bytes 2+3
	BYTE mask7 = 0x38;	//00111000  byte 3 (least significant byte)
	BYTE mask8 = 0x07;	//00000111	byte 3 

	decData[0][0] = ((data[0] & mask1) >> 5) + 'A';
	decData[0][1] = ((data[0] & mask2) >> 2) + '1';
	if (numOfChar == 1)
		return;
	decData[1][0] = (((data[0] & mask3a) << 1) | ((data[1] & mask3b) >> 7)) + 'A';
	decData[1][1] = ((data[1] & mask4) >> 4) + '1';
	if (numOfChar == 2)
		return;
	decData[2][0] = ((data[1] & mask5) >> 1) + 'A';
	decData[2][1] = (((data[1] & mask6a) << 2) | ((data[2] & mask6b) >> 6)) + '1';
	if (numOfChar == 3)
		return;
	decData[3][0] = ((data[2] & mask7) >> 3) + 'A';
	decData[3][1] = (data[2] & mask8) + '1';
}
void freeCPL(chessPosList* lst) {
	chessPosCell* curr = lst->head, *prev;
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(lst);
}
