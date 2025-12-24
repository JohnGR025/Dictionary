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

static dictionary_size = 0;

int main(int argc, char const *argv[])
{
    
    return 0;
}

//Function Factory
unsigned int strtohash(char* str){
     unsigned int hash=0;
     while(*str){
        hash=*str+31*hash;
        str++;
     }
     return hash%dictionary_size;
}