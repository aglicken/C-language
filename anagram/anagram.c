#include "anagram.h"
/*Anne Glickenhaus, aglicken, 04/15/2019, CIS 415 Project 0
This is my own work, brain storming and white board work was done with Alyssa Kelley, Zach Bower, 
and Luke Peyrala.
https://www.tutorialspoint.com/learn_c_by_examples/program_to_sort_string_characters_in_c.htm assisited 
in an alphabetical sorting function, and a swap function was used from a prior 314 function. 
https://www.hackerearth.com/practice/data-structures/linked-list/singly-linked-list/tutorial/ assisted 
in a better understanding of linked lists. https://www.youtube.com/watch?v=vLnPwxZdW4Y assisted in 
learning switch statements used in main, to clean up a long series of elif statements.
This program reads in words from a dictionary and sorts them into anagrams. 
If words share an anagram family, the anagram is printed out with a word count, followed by the list of words.
*/


/*Allocates memory for the struct StringList, returns a pointer to a new struct StringList*/
struct StringList *MallocSList(char *word){  // Pointer to list of words
	
	int len = strlen(word); //Length of word.
	
	struct StringList *SList = malloc(sizeof(struct StringList)); // Points to struct.
	
	SList -> Word = (char *) malloc(sizeof(char) * (len+1));  // Allocates Word space for size of word.
	
	strcpy(SList -> Word, word); // Copies word into memory.
	
	SList -> Word[len] = '\0'; // Adds null terminator to end of word in space allocated for it.
	
	SList -> Next = NULL; // Set next pointer to NULL.
	 
	return SList; // Returns pointer to address.
}

/*Sets cur pointer equal to head and then iterates to last position and sets Next to node*/
void AppendSList(struct StringList **head, struct StringList *node){
	 
	struct StringList *cur = *head; // Address of head pointer.
	
	while(cur -> Next != NULL){
		cur = cur -> Next;
	}
	cur -> Next = node;
}

/*Frees memory allocated to StringList*/
void FreeSList(struct StringList **node){
	struct StringList *cur = *node;
	struct StringList *next = cur -> Next;
	
	while(cur != NULL){
		free(cur -> Word);
		next = cur -> Next;
		free(cur);
		cur = next;
	}
	free(cur);
}

/*Prints a StringList.*/
void PrintSList(FILE *file,struct StringList *node){
	
	while(node != NULL){
		fprintf(file, "\t%s\n",node -> Word);
		node = node -> Next;
	}
}

/*Obtains a count for a StringList.*/
int SListCount(struct StringList *node){
	// retrurns the count of words in StringList
	int ct = 0;
	
	while(node != NULL){
		ct ++;
		node = node -> Next;
	}
	return  ct;
}

/*Sorts a word alphabetically, helped by tutorialspoint.com.*/
char* sort(char *word){
	
	int len = strlen(word);
	int j, k;

	for(j=0; j< len-1; j++){
		for(k=j+1; k< len; k++){
			if(word[j]>word[k]){
				char temp;
				temp = word[j];
				word[j] = word[k];
				word[k] = temp;
			}
		}
	}
	return word;
}

/*Makes all characters in a word lowercase.*/
char* lower(char* word){
	
	int len = strlen(word);
	int i;
	
	for(i=0; i<len; i++){
		word[i] = (unsigned char) tolower(word[i]);
	}
	return word;
}

/*Allocates memory for the struct AnagramList.*/
struct AnagramList* MallocAList(char *word){
	
	int len = strlen(word); //Length of word.
	
	struct StringList *SList = MallocSList(word); //Allocates memory for the word.

	struct AnagramList *AList = malloc(sizeof(struct AnagramList)); //Allocates memory for the struct.

	AList -> Anagram = malloc(sizeof(char) * (len + 1)); //Allocates memory for anagram of word.
	
	char* word_copy = strdup(word); //Copies word.
	word_copy = lower(word_copy); //Makes copy lower case.
	word_copy = sort(word_copy); //Sorts copy alphabetically.
	
	strcpy(AList -> Anagram, word_copy); //Copies the anagram into struct.
	
	AList -> Words = SList;
	AList -> Next = NULL;
	
	free(word_copy); //Free the copy of word.
	return AList; // returns pointer to address
}

/*Frees memory allocated for AnagramList.*/
void FreeAList(struct AnagramList **node){
	
	struct AnagramList *cur = *node;
	struct AnagramList *next = cur -> Next;
	
	while(cur != NULL){
		FreeSList(&cur->Words);
		free(cur -> Anagram);
		next = cur -> Next;
		free(cur);
		cur = next;
	}
}

/*Prints an AnagramList.*/
void PrintAList(FILE *file,struct AnagramList *node){
	int a_ct = 0;
	
	while(node != NULL){	
		a_ct = SListCount(node -> Words); // count for anagram

		if(a_ct > 1){
			fprintf(file, "%s:%d\n", node->Anagram, a_ct);
			PrintSList(file, node->Words);
		}
		node = node -> Next;
	}
}

void AddWordAList(struct AnagramList **node, char *word){

	//case 1: New node that has been uninitialized.
	if(*node == NULL){ // If the node is NULL, we need to allocate memory for the word
		*node = MallocAList(word);
		return;
	}
	
	else{
	//case 2: Checking to see if current anagram is in list of anagrams.
		struct AnagramList *cur_position = *node; //new head of list.
		char* cur_anagram = strdup(word); // Make a copy of the word.
		cur_anagram = lower(cur_anagram); // Make word lower case.
		cur_anagram = sort(cur_anagram); // Sort word alphabetically.
		
		struct AnagramList * end = 0;//To keep track of end of anagram list incase current anagram is not found.
		
		while(cur_position != NULL){ /* While current node position is not NULL, check to see if the cur anagram is already 
			in the list of anagrams.*/
			end = cur_position; // Keeping track of last position before it becomes NULL
			if(strcmp(cur_position->Anagram, cur_anagram) == 0){ /*If current anagram matches the Anagram pointed to by 
				current position.*/
				struct StringList *SList = MallocSList(word); // Make memory for the word.
				AppendSList(&(cur_position -> Words), SList); //Append the word to SList.
				free(cur_anagram); //Free copy of word.
				return;
			}
			cur_position = cur_position -> Next; // Set to the next position.
		}
	//case 3: Did not match current anagram to list of anagrams, append to end of anagram list.	
	struct AnagramList *AAList = MallocAList(word);
	
	end -> Next = AAList; // Set the end of the anagram list to the anagram of word.
	free(cur_anagram); //Free copy of word.
	return;
	}
	
}


