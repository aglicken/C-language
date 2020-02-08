#include "questionnaire.h"

int str_length(char * string)
{
    int len = 0; 

    for (int i=0; string[i] != 0; i++)
    {
    	len++;
    }

    if (len > 100)
    {
    	printf(BOLD_RED);
        printf("ERROR: Seems like you are entering something too long. Please consender your answer.\n");
        printf(RESET);
        exit(EXIT_FAILURE);
    }

    return len;
}

void illitalize_basic_info(Person * current_user)
{
	//(*current_user) = malloc(sizeof(current_user));

	(current_user) -> age = 0;
	(current_user) -> answer_1 = 0;
	(current_user) ->  answer_2 = 0;
	(current_user) ->  answer_3 = 0;
	(current_user) ->  answer_4 = 0;
	(current_user) ->  answer_5 = 0;
	(current_user) ->  answer_6 = 0;
	(current_user) ->  answer_7 = 0;
	(current_user) ->  answer_8 = 0;
	(current_user) ->  answer_9 = 0;
	(current_user) ->  answer_10 = 0;

}


void ask_basic_info(Person * current_user)
{
	char * line_break = "\n* - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *\n";

	char first_name[100];
	char last_name[100];
	int age = 0;
	char age_description[100];
	int gender = 0;
	char gender_description[100];
	char email_address[100];
	char confirmation[1];
	char confirmation2[1];

	printf(GREEN);
	puts("\nPlease enter your first name: \n");
	scanf("%s", first_name);
	//current_user -> first_name = first_name;
	current_user -> first_name = malloc(sizeof(char) * strlen(first_name));
	strcpy(current_user -> first_name, first_name);

	puts("\nPlease enter your last name: \n");
	scanf("%s", last_name);

	current_user -> last_name = malloc(sizeof(char) * strlen(last_name));
	strcpy(current_user -> last_name, last_name);
	printf(RESET);

	str_length(first_name); // error checking length does not exceed limits
	str_length(last_name);

	printf(BOLD_MAG);
	printf("%s", line_break);
	printf(RESET);


	printf(BLUE);
	printf("\nThanks for entering your name, %s %s.\n", current_user -> first_name, current_user -> last_name);
	printf("You will now be asked a few more questions to get to know more about you.\n"); 
	printf("Please know that the next few questions are");
	printf(BOLD_BLUE);
	printf(" mandatory.\n");
	printf(RESET);

	printf(BOLD_MAG);
	printf("%s", line_break);
	printf(RESET);

	printf(CYAN);
	printf("\nPlease select your age range out of these 5 options: \n");
	printf("\nOption 1: 18-23 \n");
	printf("\nOption 2: 24-29 \n");
	printf("\nOption 3: 30-35 \n");
	printf("\nOption 4: 36-40 \n");
	printf("\nOption 5: 41+ \n");
	puts("\nPlease enter 1-5 to select your answer: \n");
	scanf("%d", &age);

	current_user -> age = age;

	while ( age != 1 && age != 2 && age != 3 && age != 4 && age != 5 )
	{
		printf(BOLD_RED);
		printf("\nError: Please enter your age range from the options 1-5. \n");
		scanf("%d", &age);
		current_user -> age = age;
		printf(RESET);
	}

	if (age == 1)
	{
		strcpy(age_description, "18-23");
	}

	if (age == 2)
	{
		strcpy(age_description, "24-29");
	}

	if (age == 3)
	{
		strcpy(age_description, "30-35");
	}

	if (age == 4)
	{
		strcpy(age_description, "36-40");
	}

	if (age == 5)
	{
		strcpy(age_description, "41+");
	}

	printf(RESET);

	printf(BOLD_MAG);
	printf("%s", line_break);
	printf(RESET);

	printf(GREEN);
	printf("\nPlease enter your gender out of these 2 options: \n");
	printf("\nOption 1: Male \n");
	printf("\nOption 2: Female \n");

	puts("\nPlease enter 1-2 to select your answer: \n");
	scanf("%d", &gender);

	current_user -> gender = gender;
	printf(RESET);

	while ( gender != 1 && gender != 2 )
	{
		printf(BOLD_RED);
		printf("\nError: Please enter your gender from the options 1-2. \n");
		scanf("%d", &gender);
		current_user -> gender = gender;
		printf(RESET);
	}

	if (gender == 1)
	{
		strcpy(gender_description, "Male");
	}
	if (gender == 2)
	{
		strcpy(gender_description, "Female");
	}

	printf(BOLD_MAG);
	printf("%s", line_break);
	printf(RESET);

	printf(BLUE);
	puts("\nPlease enter your email address: \n Note: Your email address must be under 100 characters.\n");
	scanf("%s", email_address);

	current_user -> email_address = malloc(sizeof(char) * strlen(email_address));
	current_user -> email_address = email_address;

	printf(RESET);

	str_length(email_address);

	printf(BOLD_MAG);
	printf("%s", line_break);
	printf(RESET);

	printf(CYAN);
	printf("\nThank you %s for that information. Can you please verify that the\n", first_name);
	printf("following information is correct and confirm that we have your permission\n");
	printf("to release your information to your potential match?\n");
	printf("\nHere is the information we have: \n");
	printf(RESET);

	printf(BOLD_MAG);
	printf("%s", line_break);
	printf(RESET);

	printf(CYAN);
	printf("\nYour first name is %s and your last name is %s.\n", current_user -> first_name, current_user -> last_name);
	printf("You are in the age range %s, and you identify as %s.\n", age_description, gender_description);
	printf("Your email address is %s.\n", current_user -> email_address);
	printf(RESET);

	printf(BOLD_MAG);
	printf("%s", line_break);
	printf(RESET);

	printf(CYAN);
	puts("\nPlease enter Y indicating everything is correct and we have your permission");
	printf("to move forward, or N to cancel the matching process: \n");
	scanf("%s", confirmation);
	printf(RESET);

	while(strcmp(confirmation, "N") != 0 && strcmp(confirmation, "Y") != 0)
	{
		printf(BOLD_RED);
		printf("\nError: Please inciate Y or N.\n");
		scanf("%s", confirmation);
		printf(RESET);
	}

	if (strcmp(confirmation, "N") == 0)
	{
		printf(GREEN);
		puts("\nIf you saw incorrect information and would like to try again, please enter Y, or if you do not want to continue the matching process, please enter N. \n");
		scanf("%s", confirmation2);
		printf(RESET);

		if (strcmp(confirmation2, "Y") == 0)
		{
			printf(BLUE);
			printf("\nThank you for noticing an error. You will be prompted to answer the questions again.\n");
			printf(RESET);

			printf(BOLD_MAG);
			printf("%s", line_break);
			printf(RESET);

			ask_basic_info(current_user);
		}
		
		else if (strcmp(confirmation2, "N") == 0)
		{
			printf(BLUE);
			printf("\nWe are sorry to see you leave, but we hope you find love elsewhere.\n");
			printf(RESET);
			exit(EXIT_FAILURE);
		}

		while( strcmp(confirmation2, "N") != 0 && strcmp(confirmation2, "Y") != 0)
		{
			printf(BOLD_RED);
			printf("\nError: Please inciate Y or N.\n");
			scanf("%s", confirmation2);
			printf(RESET);
		}
	}

	else if (strcmp(confirmation, "Y") == 0)
	{
		printf(BLUE);
		printf("\nThank you for confirming the information we have is correct.\n");
		printf("\nYou will now be asked 10 questions, and each questions will have 5\n");
		printf("options to choose from.\n");
		printf("\nPlease indicate your answer choice with the corresponding number.\n");
		printf(RESET);
	}

	printf(BOLD_MAG);
	printf("%s", line_break);
	printf(RESET);
}
