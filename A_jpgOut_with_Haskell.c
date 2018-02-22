/* example code that will transform color RGB to Grayscale 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jpeglib.h"
#include "hal4ImgProc.h"

#include <setjmp.h> // nicht nötig, oder?


/******************************************************************************/
int main(int argc, char* argv[]){

	/* img Matrix und öffne Datei.*/	
	unsigned char **img_Matrix; 
	FILE *pIn = fopen(argv[1],"r");

	/* Hole breite und lange des Bildes*/	
	int width,height;

	fscanf(pIn, "%d", &width);
	fscanf(pIn, "%d", &height);
	img_height = height;	
	img_width = width;
	/* Hole Speicherplatz für das Bild.*/	
	image_allocate(width, height, &img_Matrix);	
	/* Hole breite und lange des Bildes*/	
	read_to_img(width, height, &img_Matrix, pIn);
	
	/* Schreibt Bild entweder in gleiches File
	 * wie die Haskell oder in einen eigenen Namen.
	 * Je nach command line Argumenten*/	
	if (argc < 2)
	write_JPEG_file(argv[1],50,&img_Matrix);
	else 
	write_JPEG_file(argv[2],1000,&img_Matrix);

	/*Speicherplatz wieder frei geben */	
	free_img(&img_Matrix);
	fclose(pIn);
	return 0;
}
/******************************************************************************/
