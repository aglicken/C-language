#include "questionnaire.h"
#include "make_match.h"

// linker line:
// gcc -std=c11 -g -o terminal_tinder_questions.exe questionnaire.c ask_dating_questions.c make_files.c make_match.c call_python.c Terminal_Tinder_main.c


int main()
{
	Person * new_person;

	new_person = malloc(sizeof(Person));
	
	illitalize_basic_info(new_person);

	ask_basic_info(new_person);  // asks the user their basic information

	ask_10_questions(new_person);  // asks the 10 questions and saves them in the struct 

	create_user_file(new_person);  // creates the personal file for the user

	add_to_database(new_person);  // adds to the file of names.

	Match m;
	FILE *file;
	char c;
	char line[256];
	file = fopen("total_database.txt", "rt");

	if (file == NULL)
	{
		printf("Cannot access total_database.txt file.\n");
	}
	
	//MatchMem(**m);
	InitializeMatch(&m);

	ReadInDatabase(file, &m);
	getCurrentUserInfo(file, &m);
	checkMatch(file, &m);
	
	//free(m);
	fclose(file);

	if (m.match_success == true)
	{
		create_matches_file(&m);
		call_python_match(m);
	}

	else
	{
		call_python_nomatch(m);
	}

	return 0;

}