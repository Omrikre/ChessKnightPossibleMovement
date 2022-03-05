#ifndef _Q_6
#define _Q_6

#include "Q5.h"

#define CHECK6

typedef unsigned char BYTE;

int checkAndDisplayPathFromeFile(char* file_name);
bool checkValidPath(chessPosList* lst);
bool inThePositionArr(chessPos checkPos, chessPosArray* curr);
int checkIfDup(chessPosList* lst);
chessPosList* getPosFromBinFile(int size, FILE* fName);
void getDecodedData(BYTE* data, chessPos* decData, int numOfChar);


#endif