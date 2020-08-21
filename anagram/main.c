#include "anagram.h"
/*Anne Glickenhaus, aglicken, 04/15/2019, CIS 415 Project 0
This is my own work, brain storming and white board work was done with Alyssa Kelley, Zach Bower, 
and Luke Peyrala.
https://www.tutorialspoint.com/learn_c_by_examples/program_to_sort_string_characters_in_c.htm assisited 
in an alphabetical sorting function, and a swap function was used from a prior 314 function. 
https://www.hackerearth.com/practice/data-structures/linked-list/singly-linked-list/tutorial/ assisted 
in a better understandingof linked lists. https://www.youtube.com/watch?v=vLnPwxZdW4Y assisted in 
learning switch statements used in main, to clean up a long series of elif statements.
This program reads in words from a dictionary and sorts them into anagrams. 
If words share an anagram family, the anagram is printed out with a word count, followed by the list of words.*/
	
int main(int argc, char* argv[]){
	FILE *in = NULL;
	FILE *out = NULL;
	
	switch(argc){ //Used switch statements instead of else if. White board logic from Lab 2.
		case 1:
			in = stdin;
			out = stdout;
			break;
		case 2:
			in = fopen(argv[1], "r");
			out = stdout;
			break;
		case 3:
			in = fopen(argv[1], "r");
			out = fopen(argv[2], "w");
			break;
		default:
			puts("ERROR");
			exit(1);
	}
	
	char line[1024]; // buffer space to hold one line at a time
	
	struct AnagramList *AList = NULL;
	
	while(fgets(line, sizeof(line), in)){
		
		line[strlen(line) -1] = '\0';
		AddWordAList(&AList, line);
	}
	
	PrintAList(out, AList);
	
	FreeAList(&AList);
	
	fclose(in);
	fclose(out);
	
	return 0;
}