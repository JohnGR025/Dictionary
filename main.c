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
unsigned int strToHash(char* str);
void wrongStartInput(void);

//Static variables for general use:
static int dictionary_size = 0;
static int storing_type;
static char* filename;

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

    //Variables
    
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

void wrongStartInput(void)
{
    printf("You need to start the program as follows:\n");
    printf("./main <file_name> [1 or 2]\n");
    printf("Read the README for info, fellow user:)\n\n");
    exit(0); //Stop program
}