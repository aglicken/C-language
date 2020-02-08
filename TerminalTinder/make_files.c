#include "questionnaire.h"

void create_user_file(Person *current_user)
{
	FILE *file;
	// printf("We are starting to create the file and here is the last name %s\n", current_user -> last_name);

	char filename[1000];

	// strcat(filename, current_dir);
	// strcat(filename, "\\");

	strcpy(filename, current_user -> first_name);
	strcat(filename, "_");
	strcat(filename, current_user -> last_name);
	strcat(filename, ".txt"); 

	printf("This is the saved file name: %s\n", filename);

	file = fopen(filename, "w");

	if (file == NULL)
	{
		printf("Error opening the file! Try again.\n");
		exit(1);
	}

	printf("Opening the file.\n");

	fprintf(file, "First name:\n");  //line 1
	fprintf(file, "%s\n", current_user -> first_name);  //line 2
	fprintf(file, "\n");  //line 3

	fprintf(file, "Last name:\n");  //line 4
	fprintf(file, "%s\n", current_user -> last_name);  //line 5
	fprintf(file, "\n"); //line 6

	fprintf(file, "Age:\n");  //line 7
	fprintf(file, "%d - ", current_user -> age);  //line 8
		if (current_user -> age == 1 )
		{
			fprintf(file, "18-23\n");
		}

		if (current_user -> age == 2 )
		{
			fprintf(file, "24-29\n");
		}

		if (current_user -> age == 3 )
		{
			fprintf(file, "30-35\n");
		}

		if (current_user -> age == 4 )
		{
			fprintf(file, "36-40\n");
		}

		if (current_user -> age == 5 )
		{
			fprintf(file, "41+\n");
		}
	fprintf(file, "\n");  //line 8

	fprintf(file, "Gender:\n");  //line 9
	fprintf(file, "%d - ", current_user -> gender);  //line 10
		if (current_user -> gender == 1 )
		{
			fprintf(file, "Male\n");
		}

		if (current_user -> gender == 2 )
		{
			fprintf(file, "Female\n");
		}
	fprintf(file, "\n");  //line 11 

	fprintf(file, "Email address:\n");  //line 12
	fprintf(file, "%s\n", current_user -> email_address);  //line 13
	fprintf(file, "\n");  //line 14

	fprintf(file, "Q1: What is your prefered age range for your match?\n");  //line 12
	fprintf(file, "%d - ", current_user -> answer_1);  //line 13

		if (current_user -> answer_1 == 1 )
		{
			fprintf(file, "18-23\n");
		}

		if (current_user -> answer_1 == 2 )
		{
			fprintf(file, "24-29\n");
		}

		if (current_user -> answer_1 == 3 )
		{
			fprintf(file, "30-35\n");
		}

		if (current_user -> answer_1 == 4 )
		{
			fprintf(file, "36-40\n");
		}

		if (current_user -> answer_1 == 5 )
		{
			fprintf(file, "41+\n");
		}

	fprintf(file, "\n"); 

	fprintf(file, "Q2: What is your prefered gender for your match?\n");
	fprintf(file, "%d - ", current_user -> answer_2);

		if (current_user -> answer_2 == 1 )
		{
			fprintf(file, "Male\n");
		}

		if (current_user -> answer_2 == 2 )
		{
			fprintf(file, "Female\n");
		}

	fprintf(file, "\n"); 

	fprintf(file, "Q3: Out of the following, which is your animal preference?\n");
	fprintf(file, "%d - ", current_user -> answer_3);

		if (current_user -> answer_3 == 1 )
		{
			fprintf(file, "Cats\n");
		}

		if (current_user -> answer_3 == 2 )
		{
			fprintf(file, "Dogs\n");
		}

		if (current_user -> answer_3 == 3 )
		{
			fprintf(file, "Reptiles/Aquatic\n");
		}

		if (current_user -> answer_3 == 4 )
		{
			fprintf(file, "Birds\n");
		}

		if (current_user -> answer_3 == 5 )
		{
			fprintf(file, "Other\n");
		}

	fprintf(file, "\n"); 

	fprintf(file, "Q4: Out of the following, which is your food preference?\n");
	fprintf(file, "%d - ", current_user -> answer_4);

		if (current_user -> answer_4 == 1 )
		{
			fprintf(file, "Mexican Food\n");
		}

		if (current_user -> answer_4 == 2 )
		{
			fprintf(file, "Italian Food\n");
		}

		if (current_user -> answer_4 == 3 )
		{
			fprintf(file, "Asian Food\n");
		}

		if (current_user -> answer_4 == 4 )
		{
			fprintf(file, "American Food\n");
		}

		if (current_user -> answer_4 == 5 )
		{
			fprintf(file, "French Food\n");
		}

	fprintf(file, "\n"); 

	fprintf(file, "Q5: Out of the following, which is your wake-up time preference?\n");
	fprintf(file, "%d - ", current_user -> answer_5);

		if (current_user -> answer_5 == 1 )
		{
			fprintf(file, "5-7am\n");
		}

		if (current_user -> answer_5 == 2 )
		{
			fprintf(file, "8-10am\n");
		}

		if (current_user -> answer_5 == 3 )
		{
			fprintf(file, "10-12pm\n");
		}

		if (current_user -> answer_5 == 4 )
		{
			fprintf(file, "After 12pm\n");
		}

		if (current_user -> answer_5 == 5 )
		{
			fprintf(file, "No specific time.\n");
		}

	fprintf(file, "\n"); 

	fprintf(file, "Q6: Out of the following, which is your favorite season?\n");
	fprintf(file, "%d - ", current_user -> answer_6);

		if (current_user -> answer_6 == 1 )
		{
			fprintf(file, "Fall \n");
		}

		if (current_user -> answer_6 == 2 )
		{
			fprintf(file, "Winter\n");
		}

		if (current_user -> answer_6 == 3 )
		{
			fprintf(file, "Spring\n");
		}

		if (current_user -> answer_6 == 4 )
		{
			fprintf(file, "Summer\n");
		}

		if (current_user -> answer_6 == 5 )
		{
			fprintf(file, "I love them all.\n");
		}

	fprintf(file, "\n"); 

	fprintf(file, "Q7: Out of the following, which location do you want to travel to the most?\n");
	fprintf(file, "%d - ", current_user -> answer_7);

		if (current_user -> answer_7 == 1 )
		{
			fprintf(file, "Europe\n");
		}

		if (current_user -> answer_7 == 2 )
		{
			fprintf(file, "South America\n");
		}

		if (current_user -> answer_7 == 3 )
		{
			fprintf(file, "Africa\n");
		}

		if (current_user -> answer_7 == 4 )
		{
			fprintf(file, "Asia\n");
		}

		if (current_user -> answer_7 == 5 )
		{
			fprintf(file, "I don't like to travel.\n");
		}

	fprintf(file, "\n"); 

	fprintf(file, "Q8: Out of the following, which is your favorite subject?\n");
	fprintf(file, "%d - ", current_user -> answer_8);

		if (current_user -> answer_8 == 1 )
		{
			fprintf(file, "Math\n");
		}

		if (current_user -> answer_8 == 2 )
		{
			fprintf(file, "Science\n");
		}

		if (current_user -> answer_8 == 3 )
		{
			fprintf(file, "History\n");
		}

		if (current_user -> answer_8 == 4 )
		{
			fprintf(file, "English\n");
		}

		if (current_user -> answer_8 == 5 )
		{
			fprintf(file, "Art\n");
		}

	fprintf(file, "\n"); 

	fprintf(file, "Q9: Out of the following, which is your political standing?\n");
	fprintf(file, "%d - ", current_user -> answer_9);

		if (current_user -> answer_9 == 1 )
		{
			fprintf(file, "Democratic\n");
		}

		if (current_user -> answer_9 == 2 )
		{
			fprintf(file, "Republican\n");
		}

		if (current_user -> answer_9 == 3 )
		{
			fprintf(file, "Neither\n");
		}

		if (current_user -> answer_9 == 4 )
		{
			fprintf(file, "I hate politics.\n");
		}

	fprintf(file, "\n"); 

	fprintf(file, "Q10: Out of the following, which are you hoping for with your match?\n");
	fprintf(file, "%d - ", current_user -> answer_10);

		if (current_user -> answer_10 == 1 )
		{
			fprintf(file, "I am looking for someone to have fun with.\n");
		}

		if (current_user -> answer_10 == 2 )
		{
			fprintf(file, "I am looking for a friend.\n");
		}

		if (current_user -> answer_10 == 3 )
		{
			fprintf(file, "I am looking for someone to be in a relationship with.\n");
		}

		if (current_user -> answer_10 == 4 )
		{
			fprintf(file, "I am looking for marriage.\n");
		}

		if (current_user -> answer_10 == 5 )
		{
			fprintf(file, "I am not sure.\n");
		}

	fprintf(file, "\n"); 

	printf(BOLD_YLW);

	printf("\nWe have successfully made your dating file.\n");

	printf(RESET);

	fclose(file);

}

void add_to_database(Person *current_user)
{

	FILE *file_db;

	if (file_db == NULL)
	{
		printf("Error opening the file! Try again.\n");
		exit(1);
	}
	
	char * total_database_filename = "total_database.txt";

	//printf("This is the file I am trying to write to: %s\n", total_database_filename);

	file_db = fopen(total_database_filename, "a");

	fprintf(file_db, "\n%s %s", current_user -> first_name, current_user -> last_name);

	printf(BOLD_YLW);

	printf("\nWe are now searching our database for your perfect match!\n");

	printf(RESET);

	fclose(file_db);

}