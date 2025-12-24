/*
    Developer's Info:
    Ioannis-Nektarios Bourbouriotis
    A.M: 2022202400025
    dit24025@go.uop.gr

    Alexandros Papadopoulos
    A.M: 2022202400156
    dit24156@go.uop.gr
*/

//Libraries
#include <stdio.h>

//Static variables for general use
static dictionary_size = 0;
static storing_type = 1;

int main(int argc, char const *argv[])
{
    //Checking starting input
    if (argc<=1 || argc>3) //Wrong start input, wrong num of inputs
        wrongStartInput();
    else
    {
        if (argc==2)
        {
            //Determine counting mode
            if (strlen(argv[1])==1 && argv[1][0]=='1')
                dictionary_size = countWordsType1("dictionary");
            else if (strlen(argv[1])==1 && argv[1][0]=='2')
                dictionary_size = countWordsType2("dictionary");
            else
                wrongStartInput();
            storing_type = argv[1]; //Set the way of dictionary's storing type
            
        }
        else if (argc==3)
        {
            //Determine counting mode
            if (strlen(argv[2])==1 && argv[2][0]=='1')
                dictionary_size = countWordsType1("dictionary");
            else if (strlen(argv[2])==1 && argv[2][0]=='2')
                dictionary_size = countWordsType2("dictionary");
            else
                wrongStartInput();
            storing_type = argv[2]; //Set the way of dictionary's storing type
        }
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

int countWordsType1(FILE* fname)
{
    int count=0;
}

int countWordsType2(FILE* fname)
{

}

void wrongStartInput(void)
{
    printf("You need to start the program as follows:\n");
    printf("./main <file_name> [1 or 2]\n");
    printf("Read the README for info, fellow user:)\n\n");
    exit(0); //Stop program
}