#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*This program reads a PNM image and writes it to a new PNM.*/

typedef struct
{
	unsigned char R, G, B;
} Pixel;


typedef struct
{
	unsigned int width, height;
	Pixel *image_arr;
} Image;

/*Function takes in width. height. row and column for a pixel and returns the index
row*width + column.*/
int GetPixelIndex(int width, int height, int row, int column)
{
    if (column < 0 || column >= width)
    {
        fprintf(stderr, "You asked for a pixel index for column %d, but the only valid values are between 0 and %d\n", 
		column, width-1);
        exit(EXIT_FAILURE);
    }
    if (row < 0 || row >= height)
    {
        fprintf(stderr, "You asked for a pixel index for row %d, but the only valid values are between 0 and %d\n", 
		row, height-1);
        exit(EXIT_FAILURE);
    }
    return row*width + column;
}

/*Reads in each pixel of the image and stores in the image array defined in image struct.*/
void
ReadImage(char *filename, Image *img)
{
    fprintf(stderr, "Reading image \"%s\"\n", filename);
	
	 FILE *f_in;
	 
	 f_in = fopen(filename, "r");
	 
     char magicNum[128];
     unsigned int width, height, maxval;
     fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval); /*position indicator at pixels now*/
	 img -> width = width;
	 img -> height = height;
	 
	 img -> image_arr= malloc((sizeof(Pixel)) * width * height); /*memory allocation*/
	 
	
	 
	 int row, col;
	 Pixel x;
	 for(row=0; row < height; row++){
	 		 for(col=0; col < width; col++){
	 			 fread(&x, sizeof(Pixel), 1, f_in);
				 int ind = GetPixelIndex(width, height, row, col);
	 			 img -> image_arr[ind] = x;  // GetPixelIndex(int width, int height, int row, int column)
	  		}
	}
	fclose(f_in);
    fprintf(stderr, "Done reading image \"%s\"\n", filename);
}

/*Writes an output image array of pixels.*/
void WriteImage(char *filename, Image *img)
{ 
    fprintf(stderr, "Writing image \"%s\"\n", filename);
	
	FILE *f_out;
	f_out = fopen(filename, "w");
	unsigned int width, height;
	fprintf(f_out, "P6\n");
	fprintf(f_out, "%d %d\n", img -> width, img -> height);
	fprintf(f_out, "255\n");
	
	width = img -> width;
	height = img -> height;

	fwrite(img -> image_arr, sizeof(char), sizeof(Pixel) * width * height, f_out);
	
	fclose(f_out);
    fprintf(stderr, "Done writing image \"%s\"\n", filename);
}

/*Takes an input image and changes every pixel on a diagonal line to yellow tp produce the output image*/
void YellowDiagonal(Image *input, Image *output)
{
    fprintf(stderr, "Executing YellowDiagonal\n");
	
	unsigned int width, height;
	
	width = input -> width;
	height = input -> height;
	
	output -> image_arr = malloc(sizeof(Pixel) * width * height); 
	output -> width = width;
	output -> height = height;
	
	int row, col;
	for(row=0; row < height; row++){
 		for(col=0; col < width; col++){
			int ind = GetPixelIndex(width,height, row, col);
			if (row == col) {
				output -> image_arr[ind].R = 255;
				output -> image_arr[ind].G = 255;
		        output -> image_arr[ind].B = 0;
			}
			else output -> image_arr[ind] = input -> image_arr[ind];
		}
	}
    fprintf(stderr, "Done executing YellowDiagonal\n");
}

/*Takes two input images and combines them side by side for the output image. */
void LeftRightCombine(Image *input1, Image *input2, Image *output)
{
    fprintf(stderr, "Executing LeftRightCombine\n");
	unsigned int width1, height, width2, outputW, area1, area2;
	
	width1 = input1 -> width;
	height = input1 -> height;
	
	width2 = input2 -> width;
	outputW = (width1 + width2);
	
	area1 = sizeof(Pixel) * width1 * height;
	area2 = sizeof(Pixel) * width2 * height;
	
	output -> image_arr = malloc(area1 + area2);
	
	output -> width = outputW;
	output -> height = height;

	Pixel x,y;
	int row1, col1, row2, col2;
	
	for(row1=0; row1 < height; row1++){
	 		for(col1=0; col1 < width1; col1++){
				int i = GetPixelIndex(width1, height, row1, col1);
				x = input1 -> image_arr[i];

				int j = GetPixelIndex(outputW, height, row1, col1);
				output -> image_arr[j] = x;
		}
	}

	for(row2=0; row2 < height; row2++){
	 		for(col2 = 0; col2 < width2; col2++){
				
				int i = GetPixelIndex(width2, height, row2, col2);
				y = input2 -> image_arr[i];

				int j = GetPixelIndex(outputW, height, row2, col2);
				output -> image_arr[j+width1] = y;
		}
	}
    fprintf(stderr, "Done executing LeftRightCombine\n");
}

void
VerifyInput()
{
    FILE *f_in = fopen("2G_input.pnm", "r");
    if (f_in == NULL)
    {
        fprintf(stderr, "Cannot open 2G_input.pnm for reading.\n");
        exit(EXIT_FAILURE);
    }
    fclose(f_in);

    FILE *f_out = fopen("2G_output.pnm", "w");
    if (f_out == NULL)
    {
        fprintf(stderr, "Cannot open 2G_output.pnm for writing.\n");
        exit(EXIT_FAILURE);
    }
    fclose(f_out);
}

int main(int argc, char *argv[])
{
    VerifyInput();

    Image source_image;
    Image yellow_diagonal;
    Image left_right;

    ReadImage("2G_input.pnm", &source_image);
    WriteImage("output_of_read.pnm", &source_image);

	//if 0
    YellowDiagonal(&source_image, &yellow_diagonal);
    WriteImage("yellow_diagonal.pnm", &yellow_diagonal);
	//endif

	//if 0
    LeftRightCombine(&source_image, &yellow_diagonal, &left_right);
    WriteImage("2G_output.pnm", &left_right);
	//endif
	free(source_image.image_arr);
	free(yellow_diagonal.image_arr);
	free(left_right.image_arr);
    return 0;
}