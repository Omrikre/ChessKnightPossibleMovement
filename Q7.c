#include "Q7.h"
#include <stdio.h>

void menu() {
	int choice = 1, displayRes;
	chessPos pos;
	char* fileName;
	bool wasChosed = false, pathExists = false, isAllBoard = false;
	pathTree currPath;
	chessPos startPosition;
	chessPosList* allBoardPath = NULL;

	printMenu();
	scanf("%d", &choice);
	while (choice >= 0 && choice <= 6)
	{
		switch (choice)
		{
		case 1:
			printf("Please enter a row and a column:\n");
			getchar();
			scanf("%c%c", &pos[0], &pos[1]);
			while (!validPosition(pos))
			{
				printf("Invalid choice please choose agin\n");
				getchar();
				scanf("%c%c", &pos[0], &pos[1]);
			}
				startPosition[0] = pos[0];
				startPosition[1] = pos[1];
				wasChosed = true;
			break;
		case 2:
			if (wasChosed)
			{
				currPath = findAllPossibleKnightPaths(&startPosition);
				pathExists = true;
			}
			else
				printf("You did not enter a starting position\n");
			break;
		case 3:
			if (wasChosed)
			{
				if (pathExists == false)
				{
					currPath = findAllPossibleKnightPaths(&startPosition);
				}
				allBoardPath = findKnightPathCoveringAllBoard(&currPath);
				
				if (allBoardPath != NULL)
				{
					isAllBoard = true;
				} 
				else
					printf("There is no path covering all board");
			}
			else
				printf("You did not enter a starting position");
			break;
		case 4:
			// לא נותן לבחור מיקום
			if (wasChosed)
			{
				if (isAllBoard == false)
				{
					currPath = findAllPossibleKnightPaths(&startPosition);
					allBoardPath = findKnightPathCoveringAllBoard(&currPath);
					if (allBoardPath == NULL)
					{
						printf("There is no path covering all board");
						break;
					}
				}
				else
				{
					printf("Please enter a file name:\n");
					fileName = getFileName();  
					saveListToBinFile(fileName, allBoardPath);
				}
			}
			else
				printf("You did not enter a starting position\n");
			break;
		case 5:
			// לא עובד ישר שולח לבעיה בפתיחת קובץ
			printf("Please enter a file name:\n");
			fileName = getFileName();
			//saveListToBinFile(fileName, allBoardPath);
			displayRes = checkAndDisplayPathFromeFile("binFile.txt");
			if (displayRes == 1)
				printf("The list does not contains a valid path\n");
			if (displayRes == 2)
				printf("The path covers all the squares on the board\n");
			if (displayRes == 3)
				printf("The path does not covers all the squares on the board\n");
			if (displayRes == -1)
				printf("The file does not exist\n");
			break;
		case 6:
			printf("End of program\n");
			exit(1);
			break;

		}
		printMenu();
		scanf("%d", &choice);
	}
}

char* getFileName() {
	int logicalSize = 0, phisicalSize = 1;
	char ch;
	char* fname = (char*)malloc(phisicalSize * sizeof(char));
	checkMemoryAllocation(fname);
	getchar();
	ch = getchar();
	while (ch != '\n')
	{
		if (logicalSize == phisicalSize)
		{
			phisicalSize *= 2;
			fname = (char*)realloc(fname, phisicalSize * sizeof(char));
			checkMemoryAllocation(fname);
		}
		fname[logicalSize++] = ch;
		ch = getchar();
	}

	fname = (char*)realloc(fname, (logicalSize + 1) * sizeof(char));
	checkMemoryAllocation(fname);
	fname[logicalSize] = '\0';

	return fname;
}

bool validPosition(chessPos pos) {
	if (((pos[0] - 'A' <= BOARDSIZE && pos[0]-'A' >= 0) && (pos[1] - '1'<= BOARDSIZE && pos[1]-'1'>=0)))
		return true;
	return false;
}

void printMenu() {
	printf("1. Enter a knight's starting position\n2. Creat all possible knight paths \n3. Find a knight path covering  all board\n4. Save knight path covering all board to file\n5. Load and display path from file\n6. Exit\n");
}
