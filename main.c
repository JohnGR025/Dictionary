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

#define WORD_SIZE 50 //Size for each word

typedef struct DictionaryArray1{
    char* word;
} Darray1;
typedef struct word_chain{
    char* word;
    struct word_chain *next;
} Chain;
typedef struct DictionaryArray2{
    char* sorted_word;
    Chain *head;
} Darray2;

//Function bodies:
int countWords(char* fname);
int searchDictionaryCase1(char *word, unsigned int *pHash, unsigned int *pIndex);
int searchDictionaryCase2(char *word, unsigned int *pHash, unsigned int *pIndex);
void wordInsertionCase1(FILE *fp);
void wordInsertionCase2(FILE *fp);
void printSearchedResultCase1(char *word, unsigned int *pHash, unsigned int *pIndex);
void printSearchedResultCase2(char *word, unsigned int *pHash, unsigned int *pIndex);
unsigned int strToHash(char *str);
void sortWord(char** word);
void wrongStartInput(void);
void freeMemoryCase1(void);
void freeMemoryCase2(void);
void bufferCleaner(void);

//Static variables for general use:
static int dictionary_size = 0;
static int storing_type;
static char* filename;
/*Only one will be used*/
static Darray1* dictionary1 = NULL; //The dictionary, where the words are stored
static Darray2* dictionary2 = NULL; //The dictionary, where the words are stored

int main(int argc, char const *argv[])
{
    //Checking starting input
    if (argc<=1 || argc>3) //Wrong start input, wrong num of inputs
        wrongStartInput();
    else
    {
        int list;
        //In this case the user didn't give a specific name for the txt file 
        //so it automatically converts the file name to dictionary.txt.
        if (argc==2)
        {
            //Determine counting mode.
            if (strlen(argv[1])==1 && strcmp(argv[1],"1")==0)
                dictionary_size = countWords("dictionary.txt") + (int)(dictionary_size*0.5);
            else if (strlen(argv[1])==1 && strcmp(argv[1],"2")==0)
                //It will be an list of anagrammed words.
                list = 0; //for error appearance.
            else
                wrongStartInput();
            storing_type = atoi(argv[1]); //Set the way of dictionary's storing type
            filename = malloc(strlen("dictionary.txt") + 1);
            strcpy(filename, "dictionary.txt");
        }
        else if (argc==3)
        {
            //Save the filename by placing the .txt in the end.
            filename = malloc(strlen(argv[1]) + 5);
            strcpy(filename, argv[1]);
            filename = realloc(filename, sizeof(filename)+sizeof(".txt"));
            strcat(filename, ".txt");
            
            //Determine counting mode
            if (strlen(argv[2])==1 && strcmp(argv[2], "1") == 0)
                dictionary_size = countWords(filename) + (int)(dictionary_size*0.5);
            else if (strlen(argv[2])==1 && strcmp(argv[2], "2") == 0)
            //It will be an list of anagrammed words.
               list = 0; //for error appearence.
            else
                wrongStartInput();
            storing_type = atoi(argv[2]); //Set the way of dictionary's storing type
        }
    }

    //Open file
    FILE *words = fopen(filename, "r");
    if (words==NULL)
    {
        printf("File can't be opened!\n");
        exit(0);
    }

    //Variables
    //For the Interaction
    unsigned int hash_code = 0;
    unsigned int *pHash = &hash_code;
    unsigned int index = 0;
    unsigned int *pIndex = &index;
    int found = 0;
    //For word input from user
    char* word_taker = (char*) malloc(WORD_SIZE*sizeof(char));

    switch (storing_type) //Different interaction with dictionary based of storing_type
    {
    case 1:
        //Start of developing the dictionary
        //Make the dictionary array with the right amount of empty space for the fragmentation.
        dictionary1 = (Darray1*) malloc(sizeof(Darray1)*dictionary_size);
        wordInsertionCase1(filename);

        //Interaction
        do
        {
            printf("Give me a word to search in the dictionary (enter '-' for exit): ");
            scanf("%s", word_taker); //Read a word for search
            bufferCleaner();
            if (strcmp(word_taker, "-") == 0) //Input is empty
                break; //End of interaction
            
            found = searchDictionaryCase1(word_taker, pHash, pIndex);
            if (found == 1)
            {
                printf("The word was found!");
                printSearchedResultCase1(word_taker, pHash, pIndex);
            }
            else
                printf("This word was not found in the dictionary.\n");
            
        } while(strcmp(word_taker, "-") != 0);

        printf("Dictionary is closing...\n");
        freeMemoryCase1();
    break;
    
    case 2:
        //Start of developing the dictionary
        //Make the dictionary array with the right amount of empty space for the fragmentation.
        dictionary2 = (Darray2*) malloc(sizeof(Darray2)*dictionary_size);
        wordInsertionCase2(filename);

        //Interaction
        do
        {
            printf("Give me a word to search in the dictionary (enter '-' for exit): ");
            scanf("%s", word_taker); //Read a word for search
            bufferCleaner();
            if (strcmp(word_taker, "-") == 0) //Input is empty
                break; //End of interaction
            
            found = searchDictionaryCase2(word_taker, pHash, pIndex);
            if (found == 1)
            {
                printf("The word was found!");
                printSearchedResultCase2(word_taker, pHash, pIndex);
            }
            else
                printf("This word was not found in the dictionary.\n");
            
        } while(strcmp(word_taker, "-") != 0);

        printf("Dictionary is closing...\n");
        freeMemoryCase2();

        printf("Dictionary is closing...\n");
    break;
    }
    
    fclose(words); //Close file

    return 0;
}

//Function Factory
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

void wordInsertionCase1(FILE *fp)
{
    int i, inserted;
    unsigned int hash, start_point;
    char* word;

    //Read and store every word
    while (!feof(fp)) //Traverse all the file
    {
        fscanf(fp, "%s\n", word); //Read word into a var
        hash = strToHash(word); //Get hash
        inserted = 0;
        //Search if the word already exists
        if (dictionary1[hash].word!=NULL && strcmp(dictionary1[hash].word, word) == 0)
        {
            i = 1;
            start_point = hash;
            //Traverse the cells until found an empty one or come back to the same one
            while ((hash = hash + i % dictionary_size) != start_point) //check like a circle array
            {
                if (dictionary1[hash].word == NULL)
                {
                    //Store the word if cell empty
                    dictionary1[hash].word = strdup(word);
                    inserted = 1;
                }
                i++; //Next array cell
            }
        }
        else if (dictionary1[hash].word==NULL)
        {
            //Store the word if cell empty
            dictionary1[hash].word = strdup(word);
            inserted = 1;
        }
        //Status of word
        if (inserted)
            printf("Word: %s is in\n", word);
        else
        {
            printf("Array is full. End of insertion\n");
            return;
        }

    }
}

void wordInsertionCase2(FILE *fp)
{
    int i;
    unsigned int hash, start_point;
    char *sorted_word=NULL, *word;
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
        if (dictionary2[hash].sorted_word==NULL)
        {
            dictionary2[hash].sorted_word = strdup(sorted_word); //Store sorting word
        }
        else if (strcmp(dictionary2[hash].sorted_word, sorted_word) != 0)
        {
            i = 1;
            start_point = hash;
            while (hash = hash+i % dictionary_size != start_point)
            {
                //Find an empty space
                if (dictionary2[hash].sorted_word==NULL)
                {
                    dictionary2[hash].sorted_word = strdup(sorted_word); //Store sorting word
                    break;
                }
                i++; //Next node
            }
        }
        
        //Search the relative chain for the word or a place to store
        temp_chain = dictionary2[hash].head;
        while (temp_chain->word!=NULL)
        {
            //if word already exists, go next node
            temp_chain = temp_chain->next; //Next node
        }
        //Store the actual word
        temp_chain->word = strdup(word);
        temp_chain->next = NULL;

        //Status of word
        printf("Word: %s is in\n", word);
    }
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
            if (word[j]<word[i])
                min = j;

        }
        
        //Change of characters
        temp = word[i];
        word[i] = word[j];
        word[j] = temp;
    }
}

int searchDictionaryCase1(char *word, unsigned int *pHash, unsigned int *pIndex) //The word here is from the user's input.
{
    *pHash = strToHash(word);
    //Search dictionary
    if (strcmp(dictionary1[*pHash].word, word) == 0)
    {
        *pIndex = *pHash;
        return 1; //Found the word
    }
    else
    {
        int i = 1;
        unsigned int starting_hash = *pHash;
        *pIndex = starting_hash;
        //Traverse the cells until found an empty one or come back to the same one
        while ((*pIndex = *pIndex + i % dictionary_size) != starting_hash) //check like a circle array
        {
            if (strcmp(dictionary1[*pHash].word, word) == 0)
                return 1; //Found the word
            i++; //Next array cell
        }
    }

    return 0; //Not found
}

void printSearchedResultCase1(char *word, unsigned int *pHash, unsigned int *pIndex)
{
    //Print info
    printf("Your word: %s found in\n", word);
    printf("Hash Code: %u\n", *pHash);
    printf("Index: %u\n", *pIndex);
}

int searchDictionaryCase2(char *word, unsigned int *pHash, unsigned int *pIndex) //The word here is from the user's input.
{
    char* sorted_word=NULL;
    *pHash = strToHash(word);
    //Ready the sorted word
    sorted_word = strdup(word);
    sortWord(sorted_word);
    //Search dictionary
    if (strcmp(dictionary2[*pHash].sorted_word, sorted_word) == 0)
    {
        *pIndex = *pHash;
        return 1; //Found the word
    }
    else
    {
        int i = 1;
        unsigned int starting_hash = *pHash;
        *pIndex = starting_hash;
        //Traverse the cells until found an empty one or come back to the same one
        while ((*pIndex = *pIndex + i % dictionary_size) != starting_hash) //check like a circle array
        {
            if (strcmp(dictionary2[*pHash].sorted_word, sorted_word) == 0)
                return 1; //Found the word
            i++; //Next array cell
        }
    }

    return 0; //Not found
}

void printSearchedResultCase2(char *word, unsigned int *pHash, unsigned int *pIndex)
{
    //Print info
    printf("Your word: %s found in\n", word);
    printf("Hash Code: %u\n", *pHash);
    printf("Index: %u\n", *pIndex);
    printf("--Printing all the anagrams--\n");
    Chain *temp=NULL;
    while (temp!=NULL)
    {
        printf("%s\n", temp->word);
        temp = temp->next;
    }
    printf("--End of printing--\n");
}

void freeMemoryCase1(void)
{
    //Free allocated memory
    free(dictionary1); //Free the array
}

void freeMemoryCase2(void)
{
    int i;
    Chain *temp1=NULL, *temp2=NULL;
    for (i = 0; i < dictionary_size; i++)
    {
        //Free each chain
        temp1 = dictionary2[i].head;
        while (temp1!=NULL)
        {
            temp2 = temp1->next;
            free(temp1);
            temp1 = temp2;
        }
    }
    free(dictionary2); //Free leftover array
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