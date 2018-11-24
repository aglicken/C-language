#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 10

/*Function takes a string argument, counts the length of the string, makes sure string
is only integers and less than 10 length, and then converts the string into an integer 
by iterating over each character, multiplying by 10 and then adding the next iteration. 
Return the number as a int. Uses reverse polish notation to calculate answers by pushing and popping from
the stack.*/
typedef struct {
	int counter;
	int c_stack[MAX_STACK_SIZE];
} Stack;

void Initialize(Stack *s){  /*Initialize counter*/
	s -> counter = 0;
}

void Push(Stack *s, int x){
	
	if (s -> counter == MAX_STACK_SIZE) {
		printf("ERROR: over max stack size\n");
		exit(EXIT_FAILURE);	
	}
	
	else {
		s -> c_stack[s -> counter] = x;
		(s -> counter)++;
	}
}

int Pop(Stack *s){
	
	int x;
	x = (s -> c_stack)[(s -> counter)-1];
	(s -> counter)--;
	
	return x;	
}

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
		Stack s; // stack initialized
		Initialize(&s);
		int num1, num2, answer; 
		
		for(int i = 1; i < argc; i++) {
			char *str = argv[i]; 
			
			if (str[0] == '+' || str[0] == '-' || str[0] == 'x') {
				if (str[1] != '\0') {			/*check that there's. only one operation at a time.*/
				    printf("ERROR: operation may only be + or -\n");
				    exit(EXIT_FAILURE);
				}
				num2 = Pop(&s);
				num1 = Pop(&s);
			
				if (str[0] == '+'){              /*If operation is +, performs addition.*/
					answer = num1 + num2;
				}
			
				if (str[0] == '-'){				/*If operation is -, performs subtraction.*/
					answer = num1 - num2;
				}
			
				if (str[0] == 'x'){				/*If operation is x, performs multiplication.*/
					answer = num1 * num2;
				}
			Push(&s, answer);					/*Push answer to stack.*/
			}
			
			else {
				Push(&s, str_to_int(str));   /*if str is not an operation, convert string to int and push to stack.*/
			}
		}
		
	
	printf("The total is %d\n", answer);	
	return 0;	
	}
	
	
	
	
	
	
	