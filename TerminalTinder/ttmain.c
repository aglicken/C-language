// #include "terminal_tinder.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
	//int current_pos; // current position in array
	
	char *cur_fname; // pointer to input participant first name
	char *cur_lname; // pointer to input participant last name
	char *cur_filename;
	char *cur_email;
	
	char *database_fname; // pointer to array of first names
	char *database_lname; // pointer to array of last names
	char *database_filename;
	char *database_email;
	
	_Bool match_success;
	
} Match;


int main(int argc, char *argv[])
{
	//Match *m;
	
	FILE *fp;
	fp = fopen(argv[1], "r");
	if (fp == NULL){
		puts("Can't find file");
	}
	
	char line[256];
	//
	//  	int line_ct = 0;
	//  	char c;
	//  	// FILE *fp;
	//  	// fp = fopen(filename, "r");
	//  	for(c = getc(fp); c != EOF; c = getc(fp)){
	//  		if (c == '\n'){
	//  			line_ct++;
	//  		}
	//  	}
	
	char *name;
	
    name = fgets(line, sizeof(line), fp);
    printf("File 1: %s", line);

	
	
	// help to delete line
	/* https://stackoverflow.com/questions/20716785/how-do-i-delete-a-specific-line-from-text-file-in-c/20716810
	*/
	
	fclose(fp);
	return 0;
}





