#include "terminal_tinder.h"

void InitializeMatch(Match *m){
	m -> database_line_ct  = 0;
	m -> current_pos = 1;
	m -> match_success = 0;
}

// void MatchMem(Match **m){
// 	*m = (Match*)malloc(sizeof(Match));
// }

int GetLineCt(FILE *file){
	/*Function that counts the number of lines in a file and returns the number of lines.*/
	int num_of_lines = 1;
	char c;
	
	fseek(file, 0, SEEK_SET);  //start at top of the file
	for(c = getc(file); c != EOF; c = getc(file)){
 		if (c == '\n'){
 			num_of_lines++;
 		}
 	}
	return  num_of_lines;
}

void getCurrentUserInfo(FILE *file, Match *m){
	/*The current user is appeeended to the total_database file, and is therefor the last
	person in the file. Obtain the name of the current user and store in Match struct.*/
	
	int num_of_lines = GetLineCt(file);
 	int current_line_number = 0;
	char line[256] = {};
	
    fseek(file, 0, SEEK_SET); // start at the top of the file.
	
    char * first_name;
    char * last_name;
    char * entire_name;
	
	for(int i=0; i < num_of_lines; i++){
			
    	entire_name = fgets(line, sizeof(line), file);
   	 	current_line_number++; // keep track of where you are, always increment after fgets

    	first_name = strtok(entire_name, " ");
    	last_name = strtok(NULL, " ");

		if(current_line_number == num_of_lines){
			
			m ->cur_fname = malloc(sizeof(char)*strlen(first_name));
			strcpy( m->cur_fname, first_name); 
			m ->cur_lname = malloc(sizeof(char)*strlen(last_name));
			strcpy( m->cur_lname, last_name); 
		
		    printf("Name of current: %s %s\n", m -> cur_fname, m -> cur_lname);
		}
	}
}

void ReadInDatabase(FILE *file, Match *m){
	/*Start by reading in the name of the top person in total_database file, if no match is made
	go to next user in file.*/
	// https://www.geeksforgeeks.org/c-program-count-number-lines-file/ 
	// http://forums.devshed.com/programming-42/removing-trailing-newline-45260.html

	int num_of_lines = GetLineCt(file);
	m -> database_line_ct = GetLineCt(file);
	int current_line_number = 0;
	char c;
	char line1[256];
	
	printf("\n");
 	printf("This is the number of lines of total database: %d\n", num_of_lines);

 	fseek(file, 0, SEEK_SET); // start at the top of the file

    char * first_name;
    char * last_name;
    char * entire_name;
	for(int i= 1; i <= m -> current_pos; i++){
			entire_name = fgets(line1, sizeof(line1), file);
   			first_name = strtok(entire_name, " ");
    		last_name = strtok(NULL, "\0");
			
		if(i == m -> current_pos){
    		for (int i = 0; i < strlen(last_name); i++)
    		{
       			if ( last_name[i] == '\n' || last_name[i] == '\r' )
            		last_name[i] = '\0';
    		}
	
			m -> database_fname = malloc(sizeof(char)*strlen(first_name));
			strcpy( m->database_fname, first_name); 
	
			m -> database_lname = malloc(sizeof(char)*strlen(last_name));
			strcpy( m->database_lname, last_name); 

			printf("\n");
   	 		printf("Name of database user: %s %s\n", m -> database_fname, m -> database_lname);
			printf("\n");
		}
		current_line_number++;
	}
	m -> current_pos++;
}

_Bool checkMatch(FILE *file, Match *m){
	/*Compare current user and database user text files to see if answers were the same.*/
	//https://stackoverflow.com/questions/21114591/c-programming-read-specific-line-from-text-file
	
	char filenamecur[100] = {};
	char filenamedb[100] = {};
	
	//Store current user file name
    strcat(filenamecur, m -> cur_fname);
    strcat(filenamecur, "_");
    strcat(filenamecur, m -> cur_lname);
    strcat(filenamecur,".txt");
	printf("\n");
	m -> cur_filename = malloc(sizeof(char)*strlen(filenamecur));
	strcpy( m -> cur_filename, filenamecur);
	
	//Store database user file nam?
    strcat(filenamedb, m -> database_fname);
    strcat(filenamedb, "_");
    strcat(filenamedb, m -> database_lname);
    strcat(filenamedb,".txt");
	printf("\n");
	m -> database_filename = malloc(sizeof(char)*strlen(filenamedb));
	strcpy( m -> database_filename, filenamedb);
	
	printf("This is the filename for current: %s\n", filenamecur);
	printf("This is the filename for database: %s\n", filenamedb);
	
	//printf("Current: %s, %s\n", m -> cur_fname, m -> cur_lname);
	//printf("Database: %s, %s\n", m -> database_fname, m -> database_lname);

	FILE *datab;
	FILE *cur;
	
	char *database_filename = m -> database_filename;
	char *cur_filename = m -> cur_filename;
	
 	datab = fopen(database_filename, "r");
	cur = fopen(cur_filename, "r");

	if (datab == NULL)
	{
		printf("Cannot access database file.\n");
	}
	if (cur == NULL)
	{
		printf("Cannot access cur file.\n");
	}

	int num_of_lines = GetLineCt(datab);

	printf("**********Starting the check for a match*********\n");
	
	char linecur[256];
	char linedb[256];
	char *cur_line;
	char *data_line;
	char *tempc;
	char *tempd;
	
	int match_ct = 0;
	
	int line14 = 14; // Email address
	char *line14c;
	char *line14d;
	int line8 =  8;  // -> 17  age
	char *line8c;
	char *line8d;
	int line11 = 11; // -> 20  gender
	char *line11c;
	char *line11d;
	int line17 = 17; // -> 8  age
	char *line17c;
	char *line17d;
	int line20 = 20; // -> 11 gender
	char *line20c;
	char *line20d;
	
	fseek(cur, 0, SEEK_SET);
	fseek(datab, 0, SEEK_SET);
	int current_line_number = 1;
	
	for(int i= current_line_number; i<=line20; i++){
		tempc = fgets(linecur, sizeof(linecur), cur);
		tempd = fgets(linedb, sizeof(linedb), datab);
		
		//Email address for each user
		if(i==line14){
			line14c = malloc(sizeof(char)*strlen(linecur));
			strcpy(line14c, tempc);
			line14d = malloc(sizeof(char)*strlen(linedb));
			strcpy(line14d, tempd);
			
			//strip new line off of email address
    		for (int i = 0; i < strlen(line14c); i++)
    		{
       			if ( line14c[i] == '\n' || line14c[i] == '\r' )
            		line14c[i] = '\0';
    		}
    		for (int i = 0; i < strlen(line14d); i++)
    		{
       			if ( line14d[i] == '\n' || line14d[i] == '\r' )
            		line14d[i] = '\0';
    		}
			m -> cur_email = line14c;
			m -> database_email = line14d;
		}
		
		if(i==line8 || i==line11 || i==line17 || i==line20){
			if(i==line8){
				line8c = malloc(sizeof(char)*strlen(linecur));
				strcpy(line8c, tempc);
				line8d = malloc(sizeof(char)*strlen(linedb));
				strcpy(line8d, tempd);
			}
			if(i==line11){
				line11c = malloc(sizeof(char)*strlen(linecur));
				strcpy(line11c, tempc);
				line11d = malloc(sizeof(char)*strlen(linedb));
				strcpy(line11d, tempd);
			}
			if(i==line17){
				line17c = malloc(sizeof(char)*strlen(linecur));
				strcpy(line17c, tempc);
				line17d = malloc(sizeof(char)*strlen(linedb));
				strcpy(line17d, tempd);
			}
			if(i==line20){
				line20c = malloc(sizeof(char)*strlen(linecur));
				strcpy(line20c, tempc);
				line20d = malloc(sizeof(char)*strlen(linedb));
				strcpy(line20d, tempd);
			}	
		}
		current_line_number++;
	}
	
	if(strcmp(line8c, line17d) || strcmp(line8d, line17c) || strcmp(line11c, line20d) || strcmp(line11d, line20c)){	
		
		puts("There was no match yet");
		
		if(	m -> database_line_ct == m -> current_pos){
			return 0;
		}
		else{
			printf("\n");
			printf("\n");
			puts("^^^^^^Checking for the next potential match^^^^^^");
			ReadInDatabase(file, m);
			checkMatch(file, m);
		}
	}
	
	fseek(cur, 0, SEEK_SET);
	fseek(datab, 0, SEEK_SET);
	current_line_number = 1;
	
	for(int i=current_line_number; i <= num_of_lines; i++){
			
    	tempc = fgets(linecur, sizeof(linecur), cur);
		tempd = fgets(linedb, sizeof(linedb), datab);
		
		cur_line = malloc(sizeof(char)*strlen(linecur));
		strcpy(cur_line, tempc);

		data_line = malloc(sizeof(char)*strlen(linedb));
		strcpy(data_line, tempd);
		
		if((current_line_number>20) && !(strcmp(cur_line, data_line)) && 
			strcmp(cur_line, "\n") && strcmp(data_line, "\n")){
				match_ct++;
		}
		current_line_number++;
	}
	
	//If 5 or more questions match, then there is a match between users.
	if(match_ct >= 13){
		//printf("There was a match with %s and %s\n", m->cur_fname, m->database_fname);

		m -> match_success = 1;
	}
	
	//printf("current position: %d ****** \n", m->current_pos);
	return 0;
}

void deleteFileLine(FILE *file, Match *m){
	/*Delete the users that made a match from the total_database file.*/
	//https://www.sanfoundry.com/c-program-delete-line-text-file/
	
	// https://stackoverflow.com/questions/20716785/how-do-i-delete-a-specific-line-from-text-file-in-c/20716810
	// if match_success == 1; delete current and database (current_pos - 1) participant
	
	int data_delete = (m -> current_pos) - 1;
	int cur_delete = m -> database_line_ct;
	
	int temp=1;
	
	FILE *newfile;
	char c;
	
	c = getc(file);
	while(c != EOF){
		printf("%c", c);
		c = getc(file);
	}
	
	rewind(file);

	newfile = fopen("total_database_temp.txt", "w");
	c = getc(file);
	
	while(c != EOF){
		c = getc(file);
		if (c == '\n'){
			temp++;
			if((temp != data_delete) || (temp != cur_delete)){
				putc(c, newfile);
			}
		}
	}
	
	//fclose()
	
}

void create_matches_file(Match * m){
	FILE *file_m;

	char filename_for_matches[1000];

	strcpy(filename_for_matches, "all_the_matches.txt");

	if (file_m == NULL)
	{
		printf("Error opening the file! Try again.\n");
		exit(1);
	}

	file_m = fopen(filename_for_matches, "w");
	
	if(m -> match_success == 1){
		printf("I AM HERE\n");
		fprintf(file_m, "%s %s matched with %s %s \n", m -> cur_fname, m-> cur_lname, 
		m -> database_fname, m -> database_lname);
		fprintf(file_m, "Their email addresses are %s, and %s\n", m -> cur_email, m -> database_email);
		fprintf(file_m, "\n");
	}
}







