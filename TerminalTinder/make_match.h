#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    int current_pos; // current position in array
    
    char *cur_fname; // pointer to input participant first name
    char *cur_lname; // pointer to input participant last name
    char *cur_filename;
    char *cur_email;
    
    char *database_fname; // pointer to array of first names
    char *database_lname; // pointer to array of last names
    char *database_filename;
    char *database_email;
    
    int database_line_ct;
    
    bool match_success;
    
} Match;

void InitializeMatch(Match *m);

// allocate memory
//void MatchMem(Match **m);

int GetLineCt(FILE *filename);

void getCurrentUserInfo(FILE *filename, Match *m); // store current user (end of file) into struct

void ReadInDatabase(FILE *filename, Match *m); // read in name of database user

_Bool checkMatch(FILE *filename, Match *m);

void deleteFileLine(Match *m);

void create_matches_file(Match * m);

void call_python_nomatch(Match m);

void call_python_match(Match m);

