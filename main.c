#include "Q4.h"

void main() {

    //main q1
   // chessPosArray*** res = validKnightMoves();
   
/*
    //main q2
    chessPosList lst;
    chessPosCell* node1 = (chessPosCell*)malloc(sizeof(chessPosCell));
    chessPosCell* node2 = (chessPosCell*)malloc(sizeof(chessPosCell));
    chessPosCell* node3 = (chessPosCell*)malloc(sizeof(chessPosCell));
    node3->next = NULL;
    node3->position[0] = 'D';
    node3->position[1] = '1';

    node2->next = node3;
    node2->position[0] = 'D';
    node2->position[1] = '1';

    node1->next = node2;
    node1->position[0] = 'A';
    node1->position[1] = '2';

    lst.head = node1;
    lst.tail = node3;
    display(&lst);
    free(node1);
 

 //main q3

    pathTree pathT;
    chessPos p;
    p[0] = 'A';
    p[1] = '2';

    pathT = findAllPossibleKnightPaths(&p);
    //freePathTree(pathT);

    //main q4
    //findLongestPath(pathT.root);


   // pathTree* pathT;
    //chessPos p;
    //p[0] = 'A';
    //p[1] = '2';
    //pathT->root->position = p;
    chessPosList* check = findKnightPathCoveringAllBoard(&pathT);
 */
        /*
            //main q5
            chessPosList lst;
            chessPosCell* node1 = (chessPosCell*)malloc(sizeof(chessPosCell));
            chessPosCell* node2 = (chessPosCell*)malloc(sizeof(chessPosCell));
            chessPosCell* node3 = (chessPosCell*)malloc(sizeof(chessPosCell));
            node3->next = NULL;
            node3->position[0] = 'D';
            node3->position[1] = '1';

            node2->next = node3;
            node2->position[0] = 'C';
            node2->position[1] = '2';

            node1->next = node2;
            node1->position[0] = 'A';
            node1->position[1] = '2';

            lst.head = node1;
            lst.tail = node3;
            saveListToBinFile("binFile.txt", &lst);
        

    printf("%d",checkAndDisplayPathFromeFile("res.bin"));
*/

    menu();
}