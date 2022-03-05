#include "Q5.h"


void saveListToBinFile(char* file_name, chessPosList* pos_list)
{
	//we used only some of the masks
	BYTE mask1 = 0xE0;	//11100000  byte 1 (most significant byte - the left most one)
	BYTE mask2 = 0x1C;	//00011100  byte 1
	BYTE mask3a = 0x03, mask3b = 0x80;	//00000011 10000000 bytes 1+2 
	BYTE mask4 = 0x70;	//01110000  byte 2
	BYTE mask5 = 0x0E;	//00001110  byte 2
	BYTE mask6a = 0x01, mask6b = 0xC0;	//00000001 11000000 bytes 2+3
	BYTE mask7 = 0x38;	//00111000  byte 3 (least significant byte)
	BYTE mask8 = 0x07;	//00000111	byte 3 
	
	FILE* fb = fopen(file_name, "wb");
	checkFileIsOpen(fb, file_name);
	BYTE ch1,ch2;
	short int length = listLength(pos_list);
	fwrite(&length, sizeof(short int), 1, fb);
	chessPosCell* curr = pos_list->head; // list-node 
	BYTE word = 0; 	// word that we write to bin file 
	int i = 1; // counter that tells us what mask to use 
	BYTE d = 0;  // temp variable to save bits when overlapping - digit/letter is splitted in 2 words 
	   
		
		while (curr != NULL) 
		{
			ch1 = curr->position[0] - 'A';//0000 0010   0x04 (000)(0 01)00
			ch2 = curr->position[1] - '1';
			switch (i) {
			case 1:

				ch1 <<= 5;
				word += ch1;
				ch2 <<= 2;
				word += ch2;
				i++;
				curr = curr->next;
				break;
			case 2:
				d = ch1 % 2;
				ch1 >>= 1;
				word += ch1;
				fwrite(&word, 1, 1, fb);
				word = 0;
				word = d ? mask3b : 0; //we check if the last bit is one the bit moves to the next word | mask in binary(1000 0000)
				ch2 <<= 4;
				word += ch2;
				i++;
				curr = curr->next;
				break;
			case 3:
				ch1 <<= 1;
				word += ch1;
				d = ch2 % 4;
				ch2 >>= 2;
				word += ch2;
				fwrite(&word, 1, 1, fb);
				word = (d << 6);
				i++;
				curr = curr->next;
				break;
			case 4:
				ch1 <<= 3;
				word += ch1;
				word += ch2;
				fwrite(&word, 1, 1, fb);
				word = 0;
				i = 1;
				curr = curr->next;
				break;
			}
		}
	fclose(fb);
}

void checkFileIsOpen(FILE* f, char* fName)
{
	if (f == NULL) {
		printf("File %s could not open!\n", fName);
		exit(-1);
	}
}

int listLength(chessPosList* pos_list){
	int count = 0;
	chessPosCell* curr = pos_list->head;

	while (curr != NULL)
	{
		count++;
		curr = curr->next;
	}
	return count;
}

//פונקצייה לקריאה והדפסה מהקובץ לבדיקה
//void readFromBinFile(char* name)
//{
//	FILE* fp;
//	short int length;
//	char loc[2];
//	fp = fopen(name, "r");
//	fread(&length, sizeof(short int), 1, fp);
//	BYTE mask1 = 0xE0;	//11100000  byte 1 (most significant byte - the left most one)
//	BYTE mask2 = 0x1C;	//00011100  byte 1
//	BYTE mask3a = 0x03, mask3b = 0x80;	//00000011 10000000 bytes 1+2 
//	BYTE mask4 = 0x70;	//01110000  byte 2
//	BYTE mask5 = 0x0E;	//00001110  byte 2
//	BYTE mask6a = 0x01, mask6b = 0xC0;	//00000001 11000000 bytes 2+3
//	BYTE mask7 = 0x38;	//00111000  byte 3 (least significant byte)
//	BYTE mask8 = 0x07;	//00000111	byte 3 
//
//	BYTE word = 0; 
//	fread(&word, sizeof(char), 1, fp);
//	int count = 1;
//	for (int i = 0; i <length; i++)
//	{
//		loc[0] = 'A'; // initialization
//		loc[1] = '1';
//		
//		switch (count) {
//		case 1: 
//			loc[0] += (word & mask1) >> 5;			
//			loc[1] += (word & mask2) >> 2;
//			count++;
//			break;
//		case 2: 
//			loc[0] += (word & mask3a)<<1;
//			fread(&word, 1, 1, fp);
//			loc[0] += (word & mask3b)>>7;
//			loc[1] += (word & mask4) >> 4;
//			count++;
//			
//			break;
//		case 3: 
//			loc[0] += (word & mask5) >> 1;
//			loc[1] += (word & mask6a) << 2;		
//			fread(&word, 1, 1, fp);
//			loc[1] += (word & mask6b) >>6 ;
//			count++;
//			break; 
//		case 4:
//			loc[0] += (word & mask7) >> 3;
//			loc[1] += (word & mask8); 
//			count = 1;
//			fread(&word, 1, 1, fp);
//			break; 
//		}
//		
//		
//		printf("in hex: %x\n", word);
//		printf("The %d pair is: %c%c\n ",i, loc[0],loc[1]);
//	}
//}
//
////פונקציית	 הדפסה של הרשימה לבדיקה
//void printList(chessPosList  *lst) {
//	chessPosCell* node = lst->head; 
//	while (node->next) {
//		printf("(%c%c)->", node->position[0], node->position[1]);
//		node = node->next;
//	}
//	printf("(%c%c)\n", node->position[0], node->position[1]);
//}