#include <stdio.h> //Just to disappear the error message because of the FILE pointer.

void wordInsertionDict1(FILE *fp);
int searchDictionaryDict1(char *word, unsigned int *pHash, unsigned int *pIndex);
void printSearchedResultDict1(char *word, unsigned int *pHash, unsigned int *pIndex);
void freeMemoryDict1(void);




