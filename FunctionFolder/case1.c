//Libraries:
#include "case1.h"
#include "generalf.h"
#include "globalvariables.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void wordInsertionDict1(FILE *fp)
{
    int inserted; //If word has been inserted or not
    int count = 0; //Count of total words in
    unsigned int hash, start_point;
    char word[WORD_SIZE];

    //Read and store every word
    while (!feof(fp)) //Traverse the file
    {
        fscanf(fp, "%s\n", word); //Read word into a var
        hash = strToHash(word); //Get hash
        inserted = 0;
        //Search if the word already exists
        if (dictionary.dict1[hash].word==NULL)
        {
            //Store the word if cell empty
            dictionary.dict1[hash].word = strdup(word);
            inserted = 1;
        }
        else if (dictionary.dict1[hash].word!=NULL && strcmp(dictionary.dict1[hash].word, word) != 0)
        {
            start_point = hash;
            //Traverse the cells until found an empty one or come back to the same one
            while ((hash = (hash + 1) % dictionary_size) != start_point) //We circle through the array
            {
                if (dictionary.dict1[hash].word == NULL)
                {
                    //Store the word if cell empty
                    dictionary.dict1[hash].word = strdup(word);
                    inserted = 1;
                    break;
                }
            }
        }
        //Status of word
        if (inserted)
        {
            count++; //1+word is in
            printf("Word: %s is in", word);
            printf("%*d\n", 30-strlen(word), count);
        }
        else
        {
            if(feof(fp))
            printf("Array is full. End of insertion\n");
            return;
        }
    }
}

int  searchDictionaryDict1(char *word, unsigned int *pHash, unsigned int *pIndex) //The word here is from the user's input.
{
    *pHash = strToHash(word);
    //Search dictionary
    if ((dictionary.dict1[*pHash].word!=NULL) && (strcmp(dictionary.dict1[*pHash].word, word) == 0))
    {
        *pIndex = *pHash;
        return 1; //Found the word
    }
    else
    {
        unsigned int starting_hash = *pHash;
        *pIndex = starting_hash;
        //Traverse the cells until found an empty one or come back to the same one
        while ((*pIndex = (*pIndex + 1) % dictionary_size) != starting_hash) //check like a circle array
        {
            if (strcmp(dictionary.dict1[*pIndex].word, word) == 0)
                return 1; //Found the word
        }
    }

    return 0; //Not found
}

void printSearchedResultDict1(char *word, unsigned int *pHash, unsigned int *pIndex)
{
    //Print info
    printf("Your word: %s found in\n", word);
    printf("Hash Code: %u\n", *pHash);
    printf("Index: %u\n", *pIndex);
}

void freeMemoryDict1(void)
{
    //Free allocated memory
    for (int i = 0; i < dictionary_size; i++)
    if (dictionary.dict1[i].word != NULL)
        free(dictionary.dict1[i].word);
    free(dictionary.dict1);
}