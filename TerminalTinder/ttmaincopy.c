#include "terminal_tinder.h"

// gcc -std=c11 -g -o terminal_t.exe terminal_tinder.c ttmaincopy.c 

int main()

{
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
	//sm = *(Match*)malloc(sizeof(m));

	ReadInDatabase(file, &m);
	getCurrentUserInfo(file, &m);
	checkMatch(file, &m);
	create_matches_file(&m);
	
	//free(m);
	fclose(file);
	return 0;
}





