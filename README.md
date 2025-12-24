# Dictionary
University project, creating a dictionary while practising with the tree data type.

### Structure/Execution of program:
The user starts the program by inputing the dictionary file name 
and the way of storing the words (either with hashing table or Anagrams table).
1) The array will be static size since we can know the users input file and each cell will point to a char* variable (each word).
The word will be stored using malloc and then the array will point there.
The action that the user can control is searching by inputing a word.
Then the search happens with serial search or hashing function.
Relevant messages appear for what happened.
2) The array remains static since we input a file name but the storing differs. we use the hashing function on the sorting of the word (in ascending order) and store that word on the first cell. then that cell points to every word matching the sorting word.

As we can see, the array is a static table storing structs. In case 1 the cells store only one word that is dynamic allocated and in the case 2 they store a chain of words.

Execution command: ./main file_name [1 or 2]
file_name can be the name of the file that contains words to be inserted when the program starts. If skipped then the program assumes the name of the file as "dictionary". The numbers represent the way of how the dictionary is being stored.
1 for a table that stores a word on each cell as char*.
2 for a table that each cell stores a chain of words with the same sorting anagram.
More about it futhermore.

### Main program:
Starting by checking the input of user