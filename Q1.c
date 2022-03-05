#include "Q1.h"

chessPosArray*** validKnightMoves() {

	chessPos* tempPos;
	chessPosArray* tempArr;
	int j, tempInd = 0;
	char i;
	int ind;
	chessPosArray*** res = (chessPosArray***)malloc(sizeof(chessPosArray**) * BOARDSIZE);
	checkMemoryAllocation(res);

	for (ind = 0; ind < BOARDSIZE; ind++) {
		res[ind] = (chessPosArray**)malloc(sizeof(chessPosArray*) * COL);
		checkMemoryAllocation(res[ind]);
	}

	for (i = 'A'; i <= ROW; i++) {
		for (j = '1'; j <= COL; j++) {
			tempArr = (chessPosArray*)malloc(sizeof(chessPosArray));
			checkMemoryAllocation(tempArr);
			tempPos = (chessPos*)malloc(sizeof(chessPos) * COL);
			checkMemoryAllocation(tempPos);

			if ((i - 2) >= 'A' && (j + 1) <= COL) {
				tempPos[tempInd][0] = (i - 2);
				tempPos[tempInd][1] = (j + 1);
				tempInd++;
			}
			if ((i - 1) >= 'A' && (j + 2) <= COL) {
				tempPos[tempInd][0] = (i - 1);
				tempPos[tempInd][1] = (j + 2);
				tempInd++;
			}
			if ((i - 2) >= 'A' && (j - 1) >= '1') {
				tempPos[tempInd][0] = (i - 2);
				tempPos[tempInd][1] = (j - 1);
				tempInd++;
			}
			if ((i - 1) >= 'A' && (j - 2) >= '1') {
				tempPos[tempInd][0] = (i - 1);
				tempPos[tempInd][1] = (j - 2);
				tempInd++;
			}
			if ((i + 2) <= ROW && (j + 1) <= COL) {
				tempPos[tempInd][0] = (i + 2);
				tempPos[tempInd][1] = (j + 1);
				tempInd++;
			}
			if ((i + 1) <= ROW && (j + 2) <= COL) {
				tempPos[tempInd][0] = (i + 1);
				tempPos[tempInd][1] = (j + 2);
				tempInd++;
			}
			if ((i + 2) <= ROW && (j - 1) >= '1') {
				tempPos[tempInd][0] = (i + 2);
				tempPos[tempInd][1] = (j - 1);
				tempInd++;
			}
			if ((i + 1) <= ROW && (j - 2) >= '1') {
				tempPos[tempInd][0] = (i + 1);
				tempPos[tempInd][1] = (j - 2);
				tempInd++;
			}
			tempPos = (chessPos*)realloc(tempPos, sizeof(chessPos) * (tempInd));
			checkMemoryAllocation(tempPos);

#ifdef CHECK1
			for (int i = 0; i < tempInd; i++)
				printf("%c%c\n", tempPos[i][0], tempPos[i][1]);
#endif
			tempArr->positions = tempPos;
			tempArr->size = tempInd;
			
			res[i - 'A'][j - '1'] = tempArr;
			tempInd = 0;
		}
	}
	return res;
}
void checkMemoryAllocation(void* address) {
	if (address == NULL) {
		printf("Memory allocation failure!!!");
		exit(1);
	}
}