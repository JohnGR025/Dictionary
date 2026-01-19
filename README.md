# Two-formed Dictionary
### University project about creating a dictionary to practise with the hashing methods.

- Compile command (if makefile is not used):
gcc -o main main.c FunctionFolder/case1.c FunctionFolder/case2.c FunctionFolder/generalf.c FunctionFolder/globalvariables.c

### Structure/Execution of program:
The user starts the program by inputing the dictionary file name
and the way of storing the words (either with hashing table or Anagrams table).
The file NEEDS to be txt and each word to be the one under the other. You can input the file name without the extension.
In this project we have two tasks to accomplice that are related with the storing type of the word in the array:

1) The array will be static size since we can know the users input file and each cell will point to a char* variable (each word).
The word will be stored using calloc and then the array cell will point there.

2) The array remains static since we input a file name but the storing differs. we use the hashing function on the sorting of the word (in ascending order) and store that word on the corresponding field. Then another field points to every word matching the sorting word (to a chain of words, a list) that stays alphabetically sorted.

The array size will depend from the amount of words from the dictionary, since, for the sake of the fregmantation, we need to leave
some spaces so the insertion to be much faster.
The action that the user can control is searching by inputing a word.
Then the search happens with hashing function and serial search if needed.
Relevant messages appear for what happened.

#### -Execution command: ./main file_name [1 or 2]
file_name can be the name of the file that contains words to be inserted when the program starts. If skipped then the program assumes the name of the file as "dictionary". The numbers represent the way of how the dictionary is being stored (the filename and number selection will be the main's arguements).
- 1 for a table that stores a word on each cell as char*.
- 2 for a table that each cell stores a chain of words and also store the word in ascending sorting form.
More about it futhermore.
Also the array is of a union struct type since we can only use one form of dictionary each run.

### Main program:
Starting by checking the input of user, the one he entered when started the program.
If the number of parameters are too small or too high, then the program won't start.
Else there are two case.
1) We input a filename and a storing option (1 or 2) and those determine from what file we input words and how we store them into the array.
2) We input a storing option (1 or 2) and that means that the filename is "dictionary" (a txt file of course, and for speedy execution of the program).
Also the user gets asked for how many words of the file wants to insert.

Based on that info, we have the storing type and the file we want to extract words from. Then we calculate the array's size based on the num of words and add some extra cells for faster insertion.
Next, we enter a switch syntax and behave based on the type of the dictionary.

### Switch Cases
#### Case 1:
We instablish the dictionary of the type struct dict1.
we call the wordInsertionCase1() and insert every word into the array with the hashing method:
- Produce a hash
- Use it as index
- Input the word there, search serially for an empty spot until we hit the same spot if the dictionary[hash] cell is occupied.

Time for the interaction.
User can search for a word. The calling of searchDictionaryCase1() and printSearchedResultCase1() happens that try to find the word and display it along with the hash and the index that is located in the array. Relative messages in case of nothing found. When user ends the interaction by inputing "-", the dictionary gets unallocated and the program ends.
#### Case 2:
This case works similarily. The dictionary gets created using the dict2 struct type. We allocate memory, inserting the word using the hashing method and the chain struct in order to input words with the same hash in the same chain list.
Then comes the input option that the user can use to search words.
Each successfull search prints the word, the hash, the index it is located and every anagram there is in the relative list.
When this inputing will end with "-", then the array gets deleted and you know.

### Functions:
#### - unsigned int strToHash(char* str): 
Cycle through the str and calculate the hash code from (*str + 31*hash).
we chose the constant 31 because it's prime, creates good distribution, and can be optimized by compilers (p.x. 31 * x = (x << 5) - x). We also use the previous hash generated as seen.
Return the remainder of the division of hash and dictionary's size.

#### - int countWords(char* fname):
Open the file (fname) and for every word we increase the count. Return it

#### - void sortWord(char** word):
Classic selection sort. Sort the word in ascending order and save it to the parameter.

#### - void wordInsertionDict1(FILE *fp):
Read all the words in the file in format of "%s\n" and produce a hash for each one.
Using the hash we check the array's cells. In an empty one we store the word.
If we find a full cell, we check serially for an empty one until we reach the starting point of the search. That signals the end of the insertion since the array is completely full.

#### - void wordInsertionDict2(FILE *fp):
Read all the words in the file in format of "%s\n", sort the word and use it to produce a hash for each one.
Using the hash we check the array's cells. In an empty one we store the sorted word and in the list (Chain head) we store the actual one.
If we find a full cell, we check serially for an empty one until we reach the starting point of the search. That signals the end of the insertion since the array is completely full.
That's the half of the function. The other half stores the actual word into the chain list. 
We the hash code ready we use it to lock on the list and traverce it to find if the word already exists. If not then we store it at the end of it.
No duplicate words are being inserted of course.

#### - Chain* mergeSort(Chain* head):
Sorts the head alphabetically. Checks for a null head or a single node and returns the same parameter back.
Else, we get to work. We pass two parameters into split() that returns them full, the head has been splitted into two halfs. Then each half head gets split again by calling mergeSort() recursively. Return the result of merge() that combines the chain together.

#### - void split(Chain *head, Chain **left, Chain **right):
Uses the Slow/Fast-Pointer technique (also called the "tortoise and hare" approach) that traverses the head with a move-by-1 pointer and a move-by-2 pointer. If the fast pointer reaches the end, the slow one is already at the middle of the chain. 
The prev pointer the list's next pointers so it can cut off the list into two properly.
Changing the pointers (left, right) to point into the splitted chains.

#### - Chain* merge(Chain *left, Chain *right):
Checks to make sure we have two chains to merge othrewise it returns the chain that we have. Then, recursively assembles the chain by checking the words in each splitted chain one by one alphabetically.
Makes a list and returns it.

#### - int searchDict1(char *word, unsigned int *pHash, unsigned int *pIndex):
First, we get the hash of the word.
We search in dict1[hash] to see if the slot is full and containes the word.
Update the pIndex and return true.
Else we check serially to until we find the word or come back to where we start the search (that means we behave to the array as a circle one). Return relative value based on the result.
No duplicate words are being inserted of course.

#### - int searchDict2(char *word, unsigned int *pHash, unsigned int *pIndex):
First, sort the word using selection sort and then we get the hash of that word.
We search in dict2[hash] to see if the sorted word matches with the inputed one (sorted as well of course, equal comparisson). Return true.
Else we check serially until we find the word or come back to where we start the search (that means we behave to the array as a circle one). 
Return relative value based on the result.
Also in each case we don't check if the actual word is stored.

#### - void printSearchedResultDict1(char *word, unsigned int *pHash, unsigned int *pIndex):
Prints the word, the hash of the word and its index location in the array.

#### - void printSearchedResultDict2(char *word, unsigned int *pHash, unsigned int *pIndex):
Prints the word, the hash of the word and its index location in the array.
Also all the contents in the chain list.

#### - void freeMemoryDict1(void):
Frees first each word field and then the array itshelf.

#### - void freeMemoryDict2(void):
First frees each chain content (word field) and then the sorted_word field as well as the array itshelf.

#### - void wrongStartInput(void):
Prints error messages when the parameters are wrong determined by the main.

#### - void bufferCleaner(void):
Classic buffer cleaning using the getchar technique.