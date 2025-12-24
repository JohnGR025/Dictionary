/*
    Developer's Info:
    Ioannis-Nektarios Bourbouriotis
    A.M: 2022202400025
    dit24025@go.uop.gr

    Alexandros Papadopoulos
    A.M: 2022202400156
    dit24156@go.uop.gr
*/

//Libraries:
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Function bodies:
void wrongStartInput(void);
int countWords(char* fname);
unsigned int strToHash(char* str);

//Static variables for general use:
static int dictionary_size = 0;
static int storing_type;

int main(int argc, char const *argv[])
{
    int list;
    //Checking starting input
    if (argc<=1 || argc>3) //Wrong start input, wrong num of inputs
        wrongStartInput();
    else
    {
        if (argc==2)
        {
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
            char* filename = malloc(sizeof(argv[1]));
            strcpy(filename,argv[1]);
            filename = realloc(filename,sizeof(filename)+sizeof(".txt"));
            strcat(filename, ".txt");
            //Determine counting mode
            if (strlen(argv[2])==1 &&strcmp(argv[2],"1") == 0)
                dictionary_size = countWords(filename);
            else if (strlen(argv[2])==1 && strcmp(argv[2],"2") == 0)
               list = 0; //for error appearence.
               //It will be an list of anagrammed words.
            else
                wrongStartInput();
            storing_type = atoi(argv[2]); //Set the way of dictionary's storing type
        }
        //Make the dictionary array with the right amount of empty space for the fragmentation.
        char** dictionary = (char**)malloc(sizeof(char*)*dictionary_size + (int)(dictionary_size*0.5));
    }

    //Variables
    
    return 0;
}

//Function Factory
unsigned int strToHash(char* str)
{
     unsigned int hash=0;
     while(*str){
        hash=*str+31*hash;
        str++;
     }
     return hash%dictionary_size;
}

int countWords(char* fname)
{
    FILE *fp;
    fp = fopen(fname, "r");
    if (!fp) /*Error opening file*/
    {
        printf("Couldn't find file.\n");
        return -1;
    }
    printf("Loading...");
    int count=0;
    char dummy[50]; //Used just to count the total words.
    while(!feof(fp)){
        fscanf(fp, "%s",dummy); //Read the words
        count++; 
    }
    count--; //An extra read is happening, so we remove it.
    fclose(fp);
    printf("\nWord Count Completed.\n");
    printf("Words: %d", count);
    return count;
}

void wrongStartInput(void)
{
    printf("You need to start the program as follows:\n");
    printf("./main <file_name> [1 or 2]\n");
    printf("Read the README for info, fellow user:)\n\n");
    exit(0); //Stop program
}