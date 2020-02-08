#include "make_match.h"

void InitializeMatch(Match *m){
    m -> database_line_ct  = 0;
    m -> current_pos = 1;
    m -> match_success = false;
}

int GetLineCt(FILE *file){
    /*Function that counts the number of lines in a file. Citing 
	https://www.geeksforgeeks.org/c-program-count-number-lines-file/*/
    int num_of_lines = 1;
    char c;
    
    //fseek(file, 0, SEEK_SET);
    rewind(file);
    // this counts the number of lines in the file. Note: needs to start at 1.
    for(c = getc(file); c != EOF; c = getc(file)){
        if (c == '\n'){
            num_of_lines++;
        }
    }
    return  num_of_lines;
}

void getCurrentUserInfo(FILE *file, Match *m){
    /*The current user is appended to the total_database file, and therefor the last
     person in the file. Obtain the name of the current user and store in Match struct.*/
    
    int num_of_lines = GetLineCt(file);
    int current_line_number = 0;
    char line[256] = {};
    
    fseek(file, 0, SEEK_SET); // going to the top of the file.
    
    char * first_name;
    char * last_name;
    char * entire_name;
    
    for(int i=0; i < num_of_lines; i++){
        
        entire_name = fgets(line, sizeof(line), file);
        current_line_number++; // keep track of where you are, always increment after fgets
        
        first_name = strtok(entire_name, " ");
        last_name = strtok(NULL, " ");
        
        if(current_line_number == num_of_lines){
            
            //Store the current user first and last name in struct
            m -> cur_fname = malloc(sizeof(char) * strlen(first_name));
            strcpy( m-> cur_fname, first_name);
            m -> cur_lname = malloc(sizeof(char) * strlen(last_name));
            strcpy( m-> cur_lname, last_name);
            //printf("Name of current: %s %s\n", m -> cur_fname, m -> cur_lname);
        }
    }
}

void ReadInDatabase(FILE *file, Match *m){
    /* This function reads in a user from the database text file and stores them in the struct.
	Citing http://forums.devshed.com/programming-42/removing-trailing-newline-45260.html for stripping 
	new line character.*/
	
    int num_of_lines = GetLineCt(file);
    m -> database_line_ct = GetLineCt(file);
    int current_line_number = 0;
    char c;
    char line1[256];
    
    fseek(file, 0, SEEK_SET);
    
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
            
            //Store database user first and last name in struct.
            m -> database_fname = malloc(sizeof(char)*strlen(first_name));
            strcpy( m->database_fname, first_name);
            m -> database_lname = malloc(sizeof(char)*strlen(last_name));
            strcpy( m->database_lname, last_name);
        }
        current_line_number++;
    }
    m -> current_pos++;
}

_Bool checkMatch(FILE *file, Match *m){
    /*Compares current user and database user to see if 5 or more questions were answers the same,
	if they were then a match has been made and the m -> match_success is changed to 1. Otherwise
	no match was made and m -> match_success remains unchanged.*/
    
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
    
    //Store database user file name
    strcat(filenamedb, m -> database_fname);
    strcat(filenamedb, "_");
    strcat(filenamedb, m -> database_lname);
    strcat(filenamedb,".txt");
    printf("\n");
    m -> database_filename = malloc(sizeof(char)*strlen(filenamedb));
    strcpy( m -> database_filename, filenamedb);
    
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
    
    int num_of_lines = GetLineCt(datab); //Total number of lines in database file
    
    char linecur[256];
    char linedb[256];
    char *cur_line;
    char *data_line;
    char * tempc;
    char * tempd;

    tempc = malloc(sizeof(char) * 1000);
    tempd = malloc(sizeof(char) * 1000);
    
    int match_ct = 0; // Number of lines that match
    
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
    
	//Store each line as a temp variable unless specific line number that needs to be checked for match.
    for(int i= current_line_number; i<=line20; i++){
        tempc = fgets(linecur, sizeof(linecur), cur);
        tempd = fgets(linedb, sizeof(linedb), datab);
        
        //Email address for each user
        if(i==line14){
            line14c = malloc(sizeof(char)*strlen(linecur));
            strcpy(line14c, tempc);
            line14d = malloc(sizeof(char)*strlen(linedb));
            strcpy(line14d, tempd);
			
			//Strip new line from email address.
            for (int i = 0; i < strlen(line14c); i++)
            {
                if ( line14c[i] == '\n' || line14c[i] == '\r' )
                {
                    line14c[i] = '\0';
                }
            }
            for (int i = 0; i < strlen(line14d); i++)
            {
                if ( line14d[i] == '\n' || line14d[i] == '\r' )
                {
                    line14d[i] = '\0';
                }
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
    
    // Required lines to make a match (gender and age preferences).
    if((strcmp(line8c, line17d) != 0) || (strcmp(line8d, line17c) != 0) || (strcmp(line11c, line20d) != 0) || (strcmp(line11d, line20c) != 0))
    {

        if ((strcmp(filenamecur, filenamedb))) // if the file names are not the same, try again
        {
            if (m -> current_pos != m -> database_line_ct) // Do not compare last line to current  user
            {
                //printf("According to the program, the file names are the same!?!\n");
                ReadInDatabase(file, m);
                checkMatch(file, m);
            }
        }
    }
    else 
    {
        fseek(cur, 0, SEEK_SET);
        fseek(datab, 0, SEEK_SET);
        current_line_number = 1;
    
		//Compare questions 3-10.
        for(int i=current_line_number; i < num_of_lines; i++){
        
            tempc = fgets(linecur, sizeof(linecur), cur);
            tempd = fgets(linedb, sizeof(linedb), datab);
        
            cur_line = malloc(sizeof(char) * strlen(linecur));
            strcpy(cur_line, tempc);
            data_line = malloc(sizeof(char)*strlen(linedb));
            strcpy(data_line, tempd);
        
            if((current_line_number>20) && !(strcmp(cur_line, data_line)) &&
            strcmp(cur_line, "\n") && strcmp(data_line, "\n")){
                match_ct++;
            }
            current_line_number++;
        }
    }
    
    //If 5 or more questions match, then there is a match between users.
    if(match_ct >= 13){
        m -> match_success = 1;
    }
    return 0;
}

void create_matches_file(Match * m){
	/*If there is a match, create or add onto matches_made_database. Add the names and email
	addresses of the users who matched.*/
	
    FILE *file_m;

    char filename_for_matches[1000];

    strcpy(filename_for_matches, "matches_made_database.txt");

    if (file_m == NULL)
    {
        printf("Error opening the file! Try again.\n");
        exit(1);
    }

    file_m = fopen(filename_for_matches, "w");
    
    fprintf(file_m, "%s %s matched with %s %s\n", m -> cur_fname, m-> cur_lname, m -> database_fname, m -> database_lname);
}

