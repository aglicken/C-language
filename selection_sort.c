#include <stdio.h>
/*Sort through an array of 100 values by increasing value*/

int main()
{
    int A[100] = { 252, 657, 268, 402, 950, 66, 391, 285, 133, 577, 649, 166, 
		987, 314, 954, 214, 920, 230, 904, 801, 40, 552, 369, 682, 202, 712, 395, 
		517, 755, 603, 134, 385, 428, 941, 443, 477, 95, 647, 687, 737, 673, 19, 
		325, 697, 577, 181, 45, 964, 267, 600, 858, 145, 781, 760, 949, 508, 673, 
		717, 446, 634, 635, 679, 466, 474, 916, 855, 216, 899, 804, 159, 237, 625, 
		963, 388, 437, 682, 821, 325, 805, 876, 968, 414, 190, 434, 902, 794, 752, 
		729, 77, 243, 705, 953, 765, 637, 765, 158, 166, 599, 70, 927 };
		int n = 100;
		int i, sort, temp;
		for(i = 1; i < n; i++) {	/*Passing through the array*/
			for(sort = 0; sort < n-i; sort++) { /*Comparison between numbers*/
				if (A[sort] > A[sort+1]) {
				temp = A[sort];   /*Create temporary variable*/
				A[sort] = A[sort + 1]; /*Change the current number to the next one*/
				A[sort + 1] = temp; /*Change seecond number to the value held in temp*/
			}
			}	
	}
	for (i=0; i < n; i++) { 
		printf("\t%d", A[i]);
		if ((i+1)%10 == 0) { /*If the position of i is divisible by ten, break the line*/
			printf("\n");}
	}
}