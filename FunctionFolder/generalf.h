#include "structs.h"

Chain* merge(Chain *left, Chain *right); //Combines pieces of the chains together
void split(Chain *head, Chain **left, Chain **right); //Split chains into pieces
Chain* mergeSort(Chain *head); //Calls the above and finalize the sorting
unsigned int strToHash(char *str); //Produce hash from str
int countWords(char* fname); //Count the word in the file
void wrongStartInput(void); //Error messages
void bufferCleaner(void); //The name says it all
Chain* mergeSort(Chain *head); //Merge sort for linked list