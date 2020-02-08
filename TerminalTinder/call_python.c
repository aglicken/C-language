#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "make_match.h"


void call_python_match(Match m)
{
	char command_call[5000];
	strcpy(command_call, "python3 made_match.py ");
	strcat(command_call, m.cur_fname);
	strcat(command_call, " ");
	strcat(command_call, m.database_fname);
	strcat(command_call, " ");
	strcat(command_call, m.cur_email);
	strcat(command_call, " ");
	strcat(command_call, m.database_email);
	strcat(command_call, " ");
	strcat(command_call, m.cur_filename);
	strcat(command_call, " ");
	strcat(command_call, m.database_filename);

	printf("%s\n", command_call);

	system(command_call);

}

void call_python_nomatch(Match m)
{
	char command_call[5000];
	strcpy(command_call, "python3 no_match_made.py ");

	system(command_call);
}
