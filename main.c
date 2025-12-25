/*
    Developer's Info:
    Ioannis-Nektarios Bourbouriotis
    A.M: 2022202400025
    Email: dit24025@go.uop.gr

    Alexandros Papadopoulos
    A.M: 2022202400156
    Email: dit24156@go.uop.gr
*/

//Libraries:
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Function bodies:
int countWords(char* fname);
void searchDictionary(char **arrayD, unsigned int *pHash, unsigned int *pIndex);
void printSearchResult(unsigned int *pHash, unsigned int *pIndex);
unsigned int strToHash(char* str);
void wrongStartInput(void);

//Static variables for general use:
static int dictionary_size = 0;
static int storing_type;
static char* filename;
static char** arrayD = NULL; //The dictionary, where the words are stored

int main(int argc, char const *argv[])
{
    //Checking starting input
    if (argc<=1 || argc>3) //Wrong start input, wrong num of inputs
        wrongStartInput();
    else
    {
        int list;
        if (argc==2)
        {
            filename = "dictionary.txt";
            //Determine counting mode
            if (strlen(argv[1])==1 && strcmp(argv[1],"1") == 0)
                dictionary_size = countWords("dictionary.txt");
            else if (strlen(argv[1])==1 && strcmp(argv[1],"2") == 0)
                list = 0; //for error appearence.
                //It will be an list of anagrammed words.
            else
                wrongStartInput();
            storing_type = atoi(argv[1]); //Set the way of dictionary's storing type
            
        }
        else if (argc==3)
        {
            //Save the filename
            filename = malloc(sizeof(argv[1]) + 5); //5: strlen(.txt) + \0
            snprintf(filename, (strlen(argv[1]) + 5), "%s.txt", argv[1]); //Copy all the file name with extension
            
            //Determine counting mode
            if (strlen(argv[2])==1 && strcmp(argv[2], "1") == 0)
                dictionary_size = countWords(filename);
            else if (strlen(argv[2])==1 && strcmp(argv[2], "2") == 0)
               list = 0; //for error appearence.
               //It will be an list of anagrammed words.
            else
                wrongStartInput();
            storing_type = atoi(argv[2]); //Set the way of dictionary's storing type
        }
        //Make the dictionary array with the right amount of empty space for the fragmentation.
        char** dictionary = (char**) malloc(sizeof(char*)*(dictionary_size + (int)(dictionary_size*0.5)));
    }

    //Open file
    FILE *words = fopen(filename, "r");
    if (words==NULL)
    {
        printf("File can't be opened!\n");
        exit(0);
    }

    //Variables
    arrayD = malloc(dictionary_size * sizeof(char*)); //Allocate memory for dictionary
    char* word = NULL;
    int i = 0;

    //Start of developing and interaction of dictionary
    //Start of saving words in dictionary array
    while (!feof(filename)) //Traverse all the file
    {
        //Read and store every word
        fscanf(filename, "%s\n", word); //Read word into a var
        arrayD[i] = strdup(word); //Store var into array
        i++; //Next array cell
    }

    switch (storing_type) //Different interaction with dictionary based of storing_type
    {
    case 1:
        //Interaction
        unsigned int hash_code, index;
        unsigned int *pHash=&hash_code, *pIndex=&index;
        do
        {
            scanf("%s", word); //Read a word for search
            if (strcmp(word, "") == 0) //Input is empty
                break; //End of interaction
            
            searchDictionary(&arrayD, &word, pHash, pIndex);
            printSearchResult(&word, pHash, pIndex);
            
        } while (strcmp(word, "") == 0);
    break;
    
    case 2:

    break;
    }
    
    printf("Dictionary is closing...\n");
    freeMemory(&arrayD);

    fclose(filename); //Close file

    return 0;
}

//Function Factory
unsigned int strToHash(char* str)
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
    char dummy[50]; //Used just to count the total words.
    
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

void searchDictionary(char **arrayD, char *word, unsigned int *pHash, unsigned int *pIndex)
{
    unsigned int hash = strToHash(word);

    //Search dictionary
    
}

void printSearchResult(char *word, unsigned int *pHash, unsigned int *pIndex)
{
    //Word NOT found
    if (*pIndex == -1)
    {
        printf("Your word: %s hasn't been found\n", word);
        return;
    }
    //Word found
    printf("Your word: %s found in\n", word);
    printf("Hash Code: %u\n", *pHash);
    printf("Index: %u\n", *pIndex);
}

void freeMemory(char **arrayD)
{
    //Free allocated memory
    int i;
    for (i = 0; i < dictionary_size; i++)
    {
        free(arrayD[i]); //Free each word
    }
    free(arrayD); //Free the array
}

void wrongStartInput(void)
{
    printf("You need to start the program as follows:\n");
    printf("./main <file_name> [1 or 2]\n");
    printf("Read the README for info, fellow user:)\n\n");
    exit(0); //Stop program
}