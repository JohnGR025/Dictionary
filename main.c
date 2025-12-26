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

typedef struct DictionaryArray{
    char* word;
    int hash;
}Darray;

//Function bodies:
int countWords(char* fname);
int searchDictionary(char *word,unsigned int *pHash, unsigned int *pIndex);
void wordInsertion(FILE *fp,char *word);
void printSearchResult(char *word, unsigned int *pHash, unsigned int *pIndex);
unsigned int strToHash(char *str);
void wrongStartInput(void);
void freeMemory(void);
void bufferCleaner(void);

//Static variables for general use:
static int dictionary_size = 0;
static int storing_type;
static char* filename;
static Darray** dictionary = NULL; //The dictionary, where the words are stored

int main(int argc, char const *argv[])
{
    //Checking starting input
    if (argc<=1 || argc>3) //Wrong start input, wrong num of inputs
        wrongStartInput();
    else
    {
        int list;
        if (argc==2) //In this case the user didn't give a specific name for the txt file 
                    //so it automatically converts the file name to dictionary.txt.
        {
            //Determine counting mode.
            if (strlen(argv[1])==1 && strcmp(argv[1],"1") == 0)
                dictionary_size = countWords("dictionary.txt") + (int)(dictionary_size*0.5);
            else if (strlen(argv[1])==1 && strcmp(argv[1],"2") == 0)
                list = 0; //for error appearence.
                //It will be an list of anagrammed words.
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
            strcpy(filename,argv[1]);
            filename = realloc(filename,sizeof(filename)+sizeof(".txt"));
            strcat(filename, ".txt");
            
            //Determine counting mode
            if (strlen(argv[2])==1 && strcmp(argv[2], "1") == 0)
                dictionary_size = countWords(filename) + (int)(dictionary_size*0.5);
            else if (strlen(argv[2])==1 && strcmp(argv[2], "2") == 0)
               list = 0; //for error appearence.
               //It will be an list of anagrammed words.
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

    //Main's variables
    //Make the dictionary array with the right amount of empty space for the fragmentation.
    dictionary = (Darray**) malloc(sizeof(Darray*)*dictionary_size);
    for(int i=0;i<dictionary_size;i++){
        dictionary[i] = malloc(sizeof(Darray)); //Create memory for each cell.
        dictionary[i]->word = " ";
    }
    char* wordtaker = malloc(50);

    //Start of developing the dictionary:
    //Start of saving words in dictionary array
    wordInsertion(words,wordtaker);
    for(int i=0;i<dictionary_size;i++){
        printf("%s\n", dictionary[i]->word);

    }
    

    switch (storing_type) //Different interaction with dictionary based of storing_type
    {
    case 1:{

        //Interaction
        unsigned int hash_code = 0;
        unsigned int index = 0;
        unsigned int *pHash = &hash_code;
        unsigned int *pIndex = &index;
        int found = 0;
        do
        {
            printf("Give me a word to search in the dictionary(enter '-' for exit): ");
            scanf("%s", wordtaker); //Read a word for search
            if (strcmp(wordtaker, "-") == 0) //Input is empty
                break; //End of interaction
            
            found = searchDictionary(wordtaker,pHash,pIndex);
            if(found == 1){
                printf("The word was found!");
                printSearchResult(wordtaker, pHash, pIndex);
            }
            else
                printf("This word was not found in the dictionary.\n");
            
        } while(strcmp(wordtaker, "-") != 0);
        break;
    }
    
    case 2:

    break;
    }
    
    printf("Dictionary is closing...\n");
    freeMemory();
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

void wordInsertion(FILE *fp,char *word){
    int i=0;
    while (!feof(fp)) //Traverse all the file
    {
        //Read and store every word
        fscanf(fp, "%s\n", word); //Read word into a var
        dictionary[i]->hash = strToHash(word); //Create a hash for the word.
        if(strcmp(dictionary[dictionary[i]->hash]->word," ") == 0){
            dictionary[dictionary[i]->hash]->word = strdup(word); //Store the word in the array's field.
             dictionary[dictionary[i]->hash]->hash = dictionary[i]->hash;
        }
        else{
            int j=i;
            do{
                j++;
                if(j >= dictionary_size){
                    j = 0;
                }
                if(strcmp(dictionary[j]->word," ") == 0){
                    dictionary[j]->word = strdup(word);
                    dictionary[j]->hash = j;
                    break;
                }
            }while(strcmp(dictionary[j]->word," ") != 0 || strcmp(dictionary[j]->word,word) == 0);
        }
        i++; //Next array cell
    }
}

int searchDictionary(char *word,unsigned int *pHash, unsigned int *pIndex) //The word here is from the user's input.
{
    *pHash = strToHash(word);
    //Search dictionary
    if(dictionary[*pHash]->hash == *pHash){
        *pIndex = *pHash;
        return 1;
    }
    else{
        for(int i=*pHash+1;i<dictionary_size;i++){
            if(i >= dictionary_size){
                i = 0;
            }

            if(strcmp(dictionary[i]->word,word) == 0){
                *pIndex = *pHash;
                return 1;
                break;
            }
            if(i == *pHash)
                break;
        }
    }

    return 0;

    
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

void freeMemory(void)
{
    //Free allocated memory
    int i;
    for (i = 0; i < dictionary_size; i++)
    {
        free(dictionary[i]); //Free each word
    }
    free(dictionary); //Free the array
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