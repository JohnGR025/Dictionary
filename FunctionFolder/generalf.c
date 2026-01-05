#include "generalf.h"
#include "structs.h"
#include "globalvariables.h"
#include <stdio.h> //Just to disappear the error message because of the FILE pointer.
#include <stdlib.h> //for the exit() function
#include <string.h>

Chain* merge(Chain *left, Chain *right)
{
    Chain *result = NULL;
    
    //Check cases
    if (left == NULL)
        return right;
    if (right == NULL)
        return left;
    
    //Recursively merge the lists
    if (strcmp(left->word, right->word) <= 0)
    {
        result = left;
        result->next = merge(left->next, right);
    }
    else
    {
        result = right;
        result->next = merge(left, right->next);
    }
    
    return result;
}

void split(Chain *head, Chain **left, Chain **right)
{
    Chain *slow = head; //Moves by 1 node
    Chain *fast = head; //Moves by 2 node
    Chain *prev = NULL;
    
    //Find middle of the list
    while (fast != NULL && fast->next != NULL)
    {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    
    //Split the list
    if (prev != NULL)
        prev->next = NULL;
    
    //Set pointers
    *left = head;
    *right = slow;
}

Chain* mergeSort(Chain *head)
{
    //Check case: empty list or single node
    if (head == NULL || head->next == NULL)
        return head;
    
    Chain *left = NULL;
    Chain *right = NULL;
    
    //Split the list into two halves
    split(head, &left, &right);
    
    //Recursively sort both halves
    left = mergeSort(left);
    right = mergeSort(right);
    
    //Merge the sorted halves
    return merge(left, right);
}

unsigned int strToHash(char *str)
{
    unsigned int hash = 0;
    
    while (*str) //While not '\0'
    {
        hash = *str + 31*hash;
        str++; //Next character
    }

    return hash % dictionary_size; //Return num between [0, dictionary_size-1]
}

int countWords(char* fname)
{
    FILE *fp;
    fp = fopen(fname, "r");
    if (!fp) /*Error opening file*/
    {
        printf("Couldn't find file.\n");
        exit(1);
    }

    printf("Loading...");
    int count = -1; //Because of an extra read that will happen
    char dummy[50]; //Used just to count the total words, storing each word
    
    //Through the file we go
    while (!feof(fp))
    {
        fscanf(fp, "%s",dummy); //Read the words
        count++;
    }

    fclose(fp); //Close file
    printf("\nWord Count Completed.\n");
    printf("Words: %d\n", count);
    
    return count;
}

void wrongStartInput(void)
{
    printf("You need to start the program as follows:\n");
    printf("./main <file_name> [1 or 2]\n");
    printf("Read the README for info, fellow user:)\n\n");
    exit(0); //Stop program
}

void bufferCleaner(void)
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF); //Cleans the input buffer
}