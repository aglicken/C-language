
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_SIZE 10

/*Program that matches heart donors with recipients in an available hospital. 
Recipients and donors must be the same gender, and if there is a match for a female
and male operation at the same time, the female operation goes first.*/

typedef struct
{
	int num_elements; // element counter
	char *strings[QUEUE_SIZE]; // pointer to array of names
	int front; // index to front of array
	int back; // index to back of array
} Queue;

void InitializeQueue(Queue *q)
{
	q -> num_elements = 0;
	q -> front = 0;
	q -> back = 0;
}

void Enqueue(Queue *q,  char *str)
{
	
	if (q -> num_elements+1 >= QUEUE_SIZE) // error if there are too many elements in queue
	{
        fprintf(stderr, "Cannot work too many elements **mine**\n"); 
        exit(EXIT_FAILURE);
	}
 	q -> strings[q -> back % QUEUE_SIZE] = str; 
	q -> num_elements++;
	q -> back ++;
	
}

char * Dequeue(Queue *q)
{	
	if(q -> num_elements <= 0) // error if there are no elements in queue 
	{
        fprintf(stderr, "Cannot work no elements **mine**\n");
        exit(EXIT_FAILURE);
	}
	char *data = q -> strings [q -> front % QUEUE_SIZE]; // data is name at front position

    q -> num_elements--;
   	q -> front++;
	
	return data;
}

void
PrintQueue(Queue *q)
{
    int i;
    printf("Printing queue %p\n", q);
    printf("\tThe index for the front of the queue is %d\n", q->front);
    printf("\tThe index for the back of the queue is %d\n", q->back);
    if (q->front == q->back)
    {
        printf("\tThe queue is empty.\n");
        return;
    }
    int back = q->back;
    if (q->back < q->front)
    {
        // wrapped around, so modify indexing 
        back += QUEUE_SIZE;
    }

    for (i = q->front ; i < back ; i++)
    {
        printf("\t\tEntry[%d] = \"%s\"\n", i%QUEUE_SIZE, q->strings[i%QUEUE_SIZE]);
    }
}

void
PrettyPrintQueue(Queue *q, char *type)
{
    if ((q -> num_elements) == 0)      //  if there are no elements
    {
        printf("No unmatched entries for %s\n", type);
    }
    else
    {
        char *s;
        printf("Unmatched %s:\n", type);
        while ((q->num_elements) > 0){ //  while there are elements in the array, dequeue them.
			s = Dequeue(q);
           	printf("\t%s\n", s);
    	}
	}
}

char *NewString(char *s)
{
    int len = strlen(s);
    char *rv = malloc(len);
    strcpy(rv, s);
    rv[len-1] = '\0'; /* take out newline */
    return rv;
}

int main(int argc, char *argv[])
{
	FILE *f_in;
	f_in = fopen(argv[1], "r");
	
	/*Initialize 5 queues.*/
	Queue female_recipients;
	InitializeQueue(&female_recipients);
	
	Queue male_recipients;
	InitializeQueue(&male_recipients);
	
	Queue female_donors;
	InitializeQueue(&female_donors);
	
	Queue male_donors;
	InitializeQueue(&male_donors);
	
	Queue hospitals;
	InitializeQueue(&hospitals);
	
	char line[256]; // oversized so no risk of over filling 
	//int ct = 0;
	while(fgets(line, 256, f_in)){ 
		char *name = NewString(line + 4);
		
		// if (ct++ >= 3){    // error checking
		// 	exit(1);
		// }
		
		if (line[0] == 'R') { 
			if (line[2] == 'F'){
				Enqueue(&female_recipients,name);
			}
			if (line[2] == 'M') {
				Enqueue(&male_recipients,name);
			}
		}
		
		if (line[0] == 'D') { 
			if (line[2] == 'F'){ 
				Enqueue(&female_donors,name);
			}
			if (line[2] == 'M') { 
				Enqueue(&male_donors,name);
			}
		}
	
		if(line[0] == 'H'){ 
			char *hname = NewString(line + 2);
			Enqueue(&hospitals,hname);
		}

		if ((female_recipients.num_elements >=1) && (female_donors.num_elements >=1) && (hospitals.num_elements >= 1 ))
		{
			char *donor = Dequeue(&female_donors);
			char *recip = Dequeue(&female_recipients);
			char *hosp = Dequeue(&hospitals);
	
	    	printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
		}
	
		if ((male_recipients.num_elements >=1) && (male_donors.num_elements >=1) && (hospitals.num_elements >= 1 ))
		{
			char *donor = Dequeue(&male_donors);
			char *recip = Dequeue(&male_recipients);
			char *hosp = Dequeue(&hospitals);
	
	   	 printf("MATCH: %s donates to %s at hospital %s\n", donor, recip, hosp);
		}
	} 	

	/*Print remaining unmatched doners, recipients, and hospitals.*/
    PrettyPrintQueue(&female_donors, "female donors");
    PrettyPrintQueue(&female_recipients, "female recipients");
    PrettyPrintQueue(&male_donors, "male donors");
    PrettyPrintQueue(&male_recipients, "male recipients");
    PrettyPrintQueue(&hospitals, "hospitals");
}
