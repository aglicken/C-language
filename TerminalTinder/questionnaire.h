#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Source for color codes: http://web.theurbanpenguin.com/adding-color-to-your-output-from-c/

#define RED        "\033[0;31m"
#define BOLD_RED   "\033[1;31m"

#define GREEN      "\033[0;32m"
#define BOLD_GREEN "\033[1;32m"

#define YLW        "\033[0;33m"
#define BOLD_YLW   "\033[1;33m"

#define BLUE       "\033[0;34m"
#define BOLD_BLUE  "\033[1;34m"

#define BLU        "\033[0;34m"
#define BOLD_BLU   "\033[1;34m"

#define MAG        "\033[0;35m"
#define BOLD_MAG   "\033[1;35m"

#define CYAN       "\033[0;36m"
#define BOLD_CYAN  "\033[1;36m"

#define RESET      "\033[0m"

typedef struct
{
	char *first_name;
	char *last_name;
	char *email_address;
	char *filename;

	int age;

	int gender;

	int answer_1;
	int answer_2;
	int answer_3;
	int answer_4;
	int answer_5;
	int answer_6;
	int answer_7;
	int answer_8;
	int answer_9;
	int answer_10;
	
} Person;

int str_length(char * string);

void illitalize_basic_info(Person * p);

void ask_basic_info(Person * p);

void ask_10_questions(Person * p);

void create_user_file(Person *p);

void add_to_database(Person *p);








