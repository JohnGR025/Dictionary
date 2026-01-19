//Libraries:
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FunctionFolder/case1.h"
#include "FunctionFolder/case2.h"
#include "FunctionFolder/generalf.h"
#include "FunctionFolder/globalvariables.h"
#include "FunctionFolder/structs.h"

int main(int argc, char const *argv[])
{
    int numOfWords; //User's input for num of words inserted
    //Checking starting input
    if (argc<=1 || argc>3) //Wrong start input, wrong num of inputs
        wrongStartInput();
    else
    {
        //In this case the user didn't give a specific name for the txt file 
        //so it automatically converts the file name to dictionary.txt.
        printf("How many words do you want to insert (-1 to place all the words):");
        scanf("%d", &numOfWords);
        if (argc==2)
        {
            //Determine counting mode.
            if (strlen(argv[1])==1 && (strcmp(argv[1],"1")==0 || strcmp(argv[1],"2")==0)){
                if(numOfWords == -1)
                    dictionary_size = countWords("dictionary.txt") + (int)(dictionary_size*0.5);
                else
                    dictionary_size = numOfWords + (int)(dictionary_size*0.5);
            }

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
            strcat(filename, ".txt");
            
            //Determine counting mode
            if (strlen(argv[2])==1 && (strcmp(argv[2], "1")==0 || strcmp(argv[2], "2")==0)){
                if(numOfWords == -1)
                    dictionary_size = countWords(filename) + (int)(dictionary_size*0.5);
                else
                    dictionary_size = numOfWords + (int)(dictionary_size*0.5);
            }
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
    char word_taker[WORD_SIZE] = {0};

    switch (storing_type) //Different interaction with dictionary based of storing_type
    {
    case 1:
        //Start of developing the dictionary
        //Make the dictionary array with the right amount of empty space for the fragmentation.
        dictionary.dict1 = (Darray1*) calloc(sizeof(Darray1), dictionary_size);
        for (int i=0;i<dictionary_size;i++)
            dictionary.dict1[i].word = NULL;
        wordInsertionDict1(words,numOfWords);

        //Interaction
        do
        {
            printf("Give me a word to search in the dictionary (enter '-' for exit): ");
            scanf("%s", word_taker); //Read a word for search
            bufferCleaner();
            if (strcmp(word_taker, "-") == 0) //Input is empty
                break; //End of interaction
            
            found = searchDictionaryDict1(word_taker, pHash, pIndex);
            if (found == 1)
            {
                printf("The word was found!\n");
                printSearchedResultDict1(word_taker, pHash, pIndex);
            }
            else
                printf("This word was not found in the dictionary.\n");
            
        } while (strcmp(word_taker, "-") != 0);

        printf("Dictionary is closing...\n");
        freeMemoryDict1();
    break;
    
    case 2:
        //Start of developing the dictionary
        //Make the dictionary array with the right amount of empty space for the fragmentation.
        dictionary.dict2 = (Darray2*) calloc(sizeof(Darray2), dictionary_size);
        for (int i=0;i<dictionary_size;i++)
            dictionary.dict2[i].sorted_word = NULL;
        wordInsertionDict2(words,numOfWords);

        //Interaction
        do
        {
            printf("Give me a word to search in the dictionary (enter '-' for exit): ");
            scanf("%s", word_taker); //Read a word for search
            bufferCleaner();
            if (strcmp(word_taker, "-") == 0) //Input is empty
                break; //End of interaction
            
            found = searchDictionaryDict2(word_taker, pHash, pIndex);
            if (found == 1)
            {
                printf("The word was found!");
                printSearchedResultDict2(word_taker, pHash, pIndex);
            }
            else
                printf("This word was not found in the dictionary.\n");
            
        } while (strcmp(word_taker, "-") != 0);

        printf("Dictionary is closing...\n");
        freeMemoryDict2();
    break;
    }
    
    fclose(words); //Close file
    free(filename);

    printf("Dictionary closed\n");
    return 0;
}