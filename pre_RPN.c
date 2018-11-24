#include <stdio.h>
#include <stdlib.h>

/*Function takes a string argument, counts the length of the string, makes sure string
is only integers and less than 10 length, and then converts the string into an integer 
by iterating over each character, multiplying by 10 and then adding the next iteration. 
Return the number as a int.*/
int str_to_int(char *arg) {
	int len_ct = 0;
	while (arg[len_ct] != '\0') /*check for string length greater than 10*/
		len_ct ++;
	if (len_ct > 9) {
	printf("ERROR: number has 10 or more digits\n");
	exit(EXIT_FAILURE);	
	}
	
	int i;
	int num = 0;
	for(i=0; i < 10; i++) {
		if ((arg[i]-48) > 9) { /*check if integers are between 0 and 9*/
			printf("ERROR: number has character that is outside 0-9\n");
		 	exit(EXIT_FAILURE);
		}
	
	int negnum = 0;
	if (arg[i] == '-') { /*check if number is negative*/
		for(i=1; i<10; i++){
			if(arg[i] == '\0') break;
			int negdig_as_num = arg[i] - '0';
			negnum = ((negnum * 10) + negdig_as_num);
			}
		return (negnum *= -1);	
		}
		
	if(arg[i] == '\0') break;
		
	else {
		int dig_as_num = arg[i] - '0';
		num = ((num * 10) + dig_as_num);  
		}		
	}
	return num;
}

	int main(int argc, char *argv[])
	{
	    if (argc != 4)
	    {
	        printf("Usage: %s <integer> <+ or -> <integer>", argv[0]);
	        exit(EXIT_FAILURE);
	    }
	    char *number1 = argv[1];
	    char *operation = argv[2];
	    char *number2 = argv[3];
		
		int num1 = str_to_int(number1); /*converts sting to integer*/
		int num2 = str_to_int(number2); /*converts sting to integer*/
		
		if (operation[0] != '+' && operation[0] != '-') {
		    printf("ERROR: operation may only be + or -\n");
		    exit(EXIT_FAILURE);
		}	
		if (operation[1] != '\0') {
		    printf("ERROR: operation may only be + or -\n");
		    exit(EXIT_FAILURE);
		}
		if (operation[0] == '+')  /*checks if operation is +*/
			printf("%d\n", num1 + num2);
		if (operation[0] == '-')  /*checks if operation is -*/
			printf("%d\n", num1 - num2);
		
	return 0;	
	}