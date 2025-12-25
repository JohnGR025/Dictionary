# Dictionary
University project, creating a dictionary while practising with the tree data type.

Issues:
- One propose: in case 2 make the list as follows:
starts empty. when we input a sort word we make the node and point there. for every other node we continue to create nodes and add them to the end of list. 
so the struct is an array (metaphorical) that points to the sorting words and every cell has its own chain of words. that way we dont need to check for how many cells the array needs. 
saves time but no memory (1 extra pointer for the next cell).

### Structure/Execution of program:
The user starts the program by inputing the dictionary file name
and the way of storing the words (either with hashing table or Anagrams table).
The file NEEDS to be txt and each word to be the one under the other. You can input it without the extension.
1) The array will be static size since we can know the users input file and each cell will point to a char* variable (each word).
The word will be stored using malloc and then the array will point there.
The array size will dependent from the amount of words from the dictionary, since, for the sake of the fregmantation, we need to leave
some spaces so the insertion to be much faster.
The action that the user can control is searching by inputing a word.
Then the search happens with serial search or hashing function.
Relevant messages appear for what happened.
2) The array remains static since we input a file name but the storing differs. we use the hashing function on the sorting of the word (in ascending order) and store that word on the first cell. then that cell points to every word matching the sorting word.

As we can see, the array is a static table storing structs. In case 1 the cells store only one word that is dynamically allocated and in the case 2 they store a chain of words.

Execution command: ./main file_name [1 or 2]
file_name can be the name of the file that contains words to be inserted when the program starts. If skipped then the program assumes the name of the file as "dictionary". The numbers represent the way of how the dictionary is being stored (the filename and number selection will be the main's arguements).
1 for a table that stores a word on each cell as char*.
2 for a table that each cell stores a chain of words with the same sorting anagram.
More about it futhermore.

### Main program:
Starting by checking the input of user

### Functions:
#### unsigned int strToHash(char* str): 
Cycle through the str and calculate the hash code from (*str + 31*hash).
The constant 31 is a common choice because it's prime, creates good distribution, and can be optimized by compilers (31 * x = (x << 5) - x). We also use the previous hash generated as seen.
Return the remainder of the division of hash and dictionary's size.