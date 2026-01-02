//Libraries:
#include "case2.h"
#include "generalf.h"
#include "structs.h"
#include "globalvariables.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void wordInsertionDict2(FILE *fp)
{
    char is_same; //If found similar word
    int count = 0; //Count of total words in
    unsigned int hash, start_point;
    char *sorted_word=NULL, word[WORD_SIZE];
    Chain *temp_chain=NULL;

    //Read and store every word
    while (!feof(fp)) //Traverse all the file
    {
        fscanf(fp, "%s\n", word); //Read word into a var
        if (sorted_word!=NULL)
            free(sorted_word);
        sorted_word = strdup(word);
        sortWord(&sorted_word); //Sort the word
        hash = strToHash(sorted_word); //Produce hash from sorted word

        //Check if cell is empty
        //If the slot at the generated hash of the sorted word is full and it is not the exact same word (we check that
        //because if it is not the same word then we need to see if it is an anagram).
        while (dictionary.dict2[hash].sorted_word != NULL && strcmp(dictionary.dict2[hash].sorted_word, sorted_word) != 0)
        {
            hash = (hash + 1) % dictionary_size;
            if (hash == start_point)  // Dictionary is full
            {
                printf("Error: Dictionary is full! Cannot insert '%s' or any other word left.\n", word);
                free(sorted_word);
                return; //Stop insertion, array
            }
        }
        
        if (dictionary.dict2[hash].sorted_word == NULL) //If the slot is empty
        {
            dictionary.dict2[hash].sorted_word = strdup(sorted_word); //Place the sorted word there (fill the field sorted_word)
            dictionary.dict2[hash].head = malloc(sizeof(Chain)); //Create memory for the head since it's the first word.
            dictionary.dict2[hash].head->word = strdup(word); //Place the not-sorted word in the head->word field.
            dictionary.dict2[hash].head->next = NULL; //Set the next equal to null.
        }
        else //If the slot is not empty, then the word is an anagram and we place it in the chain of words.
        {
            Chain *curr = dictionary.dict2[hash].head;
            is_same = 0; //Assume no similar word
            while (curr != NULL)  // Check all nodes including the last
            {
                if (strcmp(curr->word, word) == 0)
                {
                    is_same = 1; //Found same word
                    break;
                }
                if (curr->next == NULL)
                    break;  //Stop at last node for insertion
                curr = curr->next; //next chain node
            }
            if (is_same)
                continue; //Next word
            
            //else, we place it in the chain of words.
            curr->next = malloc(sizeof(Chain)); //New node
            curr->next->word = strdup(word);
            curr->next->next = NULL;
        }

        //Status of word
        count++; //1+word is in
        printf("Word: %s is in", word);
        printf("%*d\n", 30-strlen(word), count);
    }

    free(sorted_word); //Free allocation
}

void printSearchedResultDict2(char *word, unsigned int *pHash, unsigned int *pIndex)
{
    //Print info
    printf("Your word: %s found in\n", word);
    printf("Hash Code: %u\n", *pHash);
    printf("Index: %u\n", *pIndex);
    printf("--Printing all the anagrams--\n");
    Chain *temp = dictionary.dict2[*pIndex].head;
    while (temp!=NULL)
    {
        printf("%s\n", temp->word);
        temp = temp->next;
    }
    printf("--End of printing--\n");
}

int searchDictionaryDict2(char *word, unsigned int *pHash, unsigned int *pIndex) //The word here is from the user's input.
{
    char* sorted_word=NULL;
    //Ready the sorted word
    sorted_word = strdup(word);
    sortWord(&sorted_word);
    *pHash = strToHash(sorted_word); //Get hash
    //Search dictionary
    if (strcmp(dictionary.dict2[*pHash].sorted_word, sorted_word) == 0)
    {
        *pIndex = *pHash;
        free(sorted_word); //Free the allocation
        return 1; //Found the word
    }
    else
    {
        unsigned int starting_hash = *pHash;
        *pIndex = starting_hash;
        //Traverse the cells until found an empty one or come back to the same one
        while ((*pIndex = (*pIndex + 1) % dictionary_size) != starting_hash) //check like a circle array
        {
            if (strcmp(dictionary.dict2[*pIndex].sorted_word, sorted_word) == 0)
            {
                free(sorted_word); //Free the allocation
                return 1; //Found the word
            }
        }
    }
    
    free(sorted_word); //Free the allocation
    return 0; //Not found
}

void freeMemoryDict2(void)
{
    int i;
    Chain *temp1=NULL, *temp2=NULL;
    for (i = 0; i < dictionary_size; i++)
    {
        //Free each chain
        temp1 = dictionary.dict2[i].head;
        while (temp1!=NULL)
        {
            temp2 = temp1->next;
            free(temp1->word); //Free word
            free(temp1); //Free node
            temp1 = temp2;
        }
    }
    free(dictionary.dict2->sorted_word); //Free word
    free(dictionary.dict2); //Free leftover array
}

void sortWord(char** word)
{
    //Implementation of selection sort
    int i, j, min;
    char temp;
    for (i = 0; i < strlen(*word)-1; i++)
    {
        min = i;
        for (j = i+1; j < strlen(*word); j++)
        {
            if ((*word)[j]<(*word)[min])
                min = j;

        }
        
        //Change of characters
        temp = (*word)[i];
        (*word)[i] = (*word)[min];
        (*word)[min] = temp;
    }
}