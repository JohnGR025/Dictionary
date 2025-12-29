#include <stdio.h> //Just to disappear the error message because of the FILE pointer.

void sortWord(char** word); //Sort word using selection sort in ascending order
void wordInsertionCase2(FILE *fp);
int searchDictionaryCase2(char *word, unsigned int *pHash, unsigned int *pIndex);
void printSearchedResultCase2(char *word, unsigned int *pHash, unsigned int *pIndex);
void freeMemoryCase2(void);