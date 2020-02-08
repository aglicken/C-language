#include "questionnaire.h"

void ask_10_questions(Person *current_user)
{	
	char * line_break = "\n* - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *\n";

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


	printf(GREEN);

	printf("\nQUESTION 1: \n");
	printf("\nWhat is your preferred age range for your match?\n");
	printf("\nOption 1: 18-23 \n");
	printf("\nOption 2: 24-29 \n");
	printf("\nOption 3: 30-35 \n");
	printf("\nOption 4: 36-40 \n");
	printf("\nOption 5: 41+ \n");

	puts("\nPlease enter 1-5 to select your answer: \n");
	scanf("%d", &answer_1);

	while (answer_1 != 1 && answer_1 != 2 && answer_1 != 3 && answer_1 != 4 && answer_1 != 5)
	{
		printf(BOLD_RED);
		printf("\nError: Please enter your answer as an interger 1-5.\n");
		scanf("%d", &answer_1);
		printf(RESET);

	}

	current_user -> answer_1 = answer_1;

	printf(RESET);

	printf(BOLD_MAG);
	printf("%s", line_break);
	printf(RESET);

	printf(BLUE);

	printf("\nQUESTION 2: \n");
	printf("\nWhat is your preferred gender for your match?\n");
	printf("\nOption 1: Male \n");
	printf("\nOption 2: Female \n");

	puts("\nPlease enter 1-2 to select your answer: \n");
	scanf("%d", &answer_2);

	while (answer_2 != 1 && answer_2 != 2 )
	{
		printf(BOLD_RED);
		printf("\nError: Please enter your answer as an interger 1-4.\n");
		scanf("%d", &answer_2);
		printf(RESET);

	}

	current_user -> answer_2 = answer_2;

	printf(RESET);

	printf(BOLD_MAG);
	printf("%s", line_break);
	printf(RESET);

	printf(CYAN);

	printf("\nQUESTION 3: \n");
	printf("\nOut of the following, which is your animal preference?\n");
	printf("\nOption 1: Cats \n");
	printf("\nOption 2: Dogs \n");
	printf("\nOption 3: Reptiles/Aquatic \n");
	printf("\nOption 4: Birds \n");
	printf("\nOption 5: Other \n");

	puts("\nPlease enter 1-5 to select your answer: \n");
	scanf("%d", &answer_3);

	while (answer_3 != 1 && answer_3 != 2 && answer_3 != 3 && answer_3 != 4 && answer_3 != 5)
	{
		printf(BOLD_RED);
		printf("\nError: Please enter your answer as an interger 1-5.\n");
		scanf("%d", &answer_3);
		printf(RESET);

	}

	current_user -> answer_3 = answer_3;

	printf(RESET);

	printf(BOLD_MAG);
	printf("%s", line_break);
	printf(RESET);

	printf(BLUE);

	printf("\nQUESTION 4: \n");
	printf("\nOut of the following, which is your food preference?\n");
	printf("\nOption 1: Mexican Food \n");
	printf("\nOption 2: Italian Food \n");
	printf("\nOption 3: Asian Food \n");
	printf("\nOption 4: American Food \n");
	printf("\nOption 5: French Food \n");

	puts("\nPlease enter 1-5 to select your answer: \n");
	scanf("%d", &answer_4);

	while (answer_4 != 1 && answer_4 != 2 && answer_4 != 3 && answer_4 != 4 && answer_4 != 5)
	{
		printf(BOLD_RED);
		printf("\nError: Please enter your answer as an interger 1-5.\n");
		scanf("%d", &answer_4);
		printf(RESET);

	}

	current_user -> answer_4 = answer_4;

	printf(RESET);

	printf(BOLD_MAG);
	printf("%s", line_break);
	printf(RESET);

	printf(GREEN);

	printf("\nQUESTION 5: \n");
	printf("\nOut of the following, which is your wake-up time preference?\n");
	printf("\nOption 1: 5-7am \n");
	printf("\nOption 2: 8-10am \n");
	printf("\nOption 3: 10-12pm \n");
	printf("\nOption 4: After 12pm \n");
	printf("\nOption 5: No specific time. \n");

	puts("\nPlease enter 1-5 to select your answer: \n");
	scanf("%d", &answer_5);

	while (answer_5 != 1 && answer_5 != 2 && answer_5 != 3 && answer_5 != 4 && answer_5 != 5)
	{
		printf(BOLD_RED);
		printf("\nError: Please enter your answer as an interger 1-5.\n");
		scanf("%d", &answer_5);
		printf(RESET);

	}

	current_user -> answer_5 = answer_5;

	printf(RESET);

	printf(BOLD_MAG);
	printf("%s", line_break);
	printf(RESET);

	printf(CYAN);

	printf("\nQUESTION 6: \n");
	printf("\nOut of the following, which is your favorite season?\n");
	printf("\nOption 1: Fall \n");
	printf("\nOption 2: Winter\n");
	printf("\nOption 3: Spring \n");
	printf("\nOption 4: Summer\n");
	printf("\nOption 5: I love them all.\n");

	puts("\nPlease enter 1-5 to select your answer: \n");
	scanf("%d", &answer_6);

	while (answer_6 != 1 && answer_6 != 2 && answer_6 != 3 && answer_6 != 4 && answer_6 != 5)
	{
		printf(BOLD_RED);
		printf("\nError: Please enter your answer as an interger 1-5.\n");
		scanf("%d", &answer_6);
		printf(RESET);

	}

	current_user -> answer_6 = answer_6;

	printf(RESET);

	printf(BOLD_MAG);
	printf("%s", line_break);
	printf(RESET);

	printf(BLUE);

	printf("\nQUESTION 7: \n");
	printf("\nOut of the following, which location do you want to travel to the most?\n");
	printf("\nOption 1: Europe \n");
	printf("\nOption 2: South America\n");
	printf("\nOption 3: Africa \n");
	printf("\nOption 4: Asia\n");
	printf("\nOption 5: I don't like to travel. \n");

	puts("\nPlease enter 1-5 to select your answer: \n");
	scanf("%d", &answer_7);

	while (answer_7 != 1 && answer_7 != 2 && answer_7 != 3 && answer_7 != 4 && answer_7 != 5)
	{
		printf(BOLD_RED);
		printf("\nError: Please enter your answer as an interger 1-5.\n");
		scanf("%d", &answer_7);
		printf(RESET);

	}

	current_user -> answer_7 = answer_7;

	printf(RESET);

	printf(BOLD_MAG);
	printf("%s", line_break);
	printf(RESET);

	printf(GREEN);

	printf("\nQUESTION 8: \n");
	printf("\nOut of the following, which is your favorite subject?\n");
	printf("\nOption 1: Math \n");
	printf("\nOption 2: Science \n");
	printf("\nOption 3: History \n");
	printf("\nOption 4: English \n");
	printf("\nOption 5: Art \n");

	puts("\nPlease enter 1-5 to select your answer: \n");
	scanf("%d", &answer_8);

	while (answer_8 != 1 && answer_8 != 2 && answer_8 != 3 && answer_8 != 4 && answer_8 != 5)
	{
		printf(BOLD_RED);
		printf("\nError: Please enter your answer as an interger 1-5.\n");
		scanf("%d", &answer_8);
		printf(RESET);

	}

	current_user -> answer_8 = answer_8;

	printf(RESET);

	printf(BOLD_MAG);
	printf("%s", line_break);
	printf(RESET);

	printf(CYAN);

	printf("\nQUESTION 9: \n");
	printf("\nOut of the following, which is your political standing?\n");
	printf("\nOption 1: Democratic \n");
	printf("\nOption 2: Republican \n");
	printf("\nOption 3: Neither \n");
	printf("\nOption 4: I hate politics \n");

	puts("\nPlease enter 1-4 to select your answer: \n");
	scanf("%d", &answer_9);

	while (answer_9 != 1 && answer_9 != 2 && answer_9 != 3 && answer_9 != 4)
	{
		printf(BOLD_RED);
		printf("\nError: Please enter your answer as an interger 1-4.\n");
		scanf("%d", &answer_9);
		printf(RESET);

	}

	current_user -> answer_9 = answer_9;

	printf(RESET);

	printf(BOLD_MAG);
	printf("%s", line_break);
	printf(RESET);

	printf(BLUE);

	printf("\nQUESTION 10: \n");
	printf("\nOut of the following, which are you hoping for with your match?\n");
	printf("\nOption 1: I am looking for someone to have fun with.\n");
	printf("\nOption 2: I am looking for a friend. \n");
	printf("\nOption 3: I am looking for someone to be in a relationship with. \n");
	printf("\nOption 4: I am looking for marriage. \n");
	printf("\nOption 5: I am not sure. \n");

	puts("\nPlease enter 1-5 to select your answer: \n");
	scanf("%d", &answer_10);

	while (answer_10 != 1 && answer_10 != 2 && answer_10 != 3 && answer_10 != 4 && answer_10 != 5)
	{
		printf(BOLD_RED);
		printf("\nError: Please enter your answer as an interger 1-5.\n");
		scanf("%d", &answer_10);
		printf(RESET);

	}

	current_user -> answer_10 = answer_10;

	printf(RESET);

	printf("\nThank you for answering those 10 questions, this will help us find your perfect match.\n");

	printf("\nOnce we finishing searching for your match, a message will pop up on the screen\n");
	printf("indicating our results. If you get a match, you both will be emailed each other's\n");
	printf("information so you can get to know each other.\n");

	printf(BOLD_MAG);
	printf("%s", line_break);
	printf(RESET);

}