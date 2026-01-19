#include <stdio.h> //Just to disappear the error message because of the FILE pointer.

void sortWord(char** word); //Sort word using selection sort in ascending order
void wordInsertionDict2(FILE *fp,int numOfWords);
int searchDictionaryDict2(char *word, unsigned int *pHash, unsigned int *pIndex);
void printSearchedResultDict2(char *word, unsigned int *pHash, unsigned int *pIndex);
void freeMemoryDict2(void);