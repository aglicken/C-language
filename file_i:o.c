#include <stdio.h>
#include <stdlib.h>

/*Main function takes in a file, reads the top 5 x 5 quadant of a 2 dimensional
array of 100 ASCII values, and prints the 5x5 to a new output file.*/
int main(int argc, char* argv[]) {
	FILE *f_in, *f_out; 
		
	f_in = fopen(argv[1], "rb");
	int arr[25];
	int x, i, j;
	
	for(i=0; i<5; i++) {  /* iterates over the rows */
		for (j=0; j<5; j++) { /*iterates over the columns*/
			fread(&x, sizeof(int), 1, f_in); /*reads over the in file one interger at a time*/
			arr[5*i + j] = x; 
		}
		fseek(f_in, 5*sizeof(int), SEEK_CUR);
	}
	
	f_out = fopen(argv[2], "w");
	
	for (i=0; i <25; i++) {
		fprintf(f_out, "%d\n", arr[i]);
	}
	
	
	fclose(f_in);
	fclose(f_out);
	return 0;
}
