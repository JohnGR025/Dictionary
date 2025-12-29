#define WORD_SIZE 50 //Size for each word

#ifndef STRUCTS_H
#define STRUCTS_H

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
typedef union Union{
    Darray1* dict1;
    Darray2* dict2;
} UnionD;

#endif