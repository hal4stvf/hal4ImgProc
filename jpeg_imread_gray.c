/*
 * example.c angepasst von der ljpeg 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jpeglib.h"


#include <setjmp.h>


/*
 * gray imread 
 */

static int img_height = 600;
static int img_width = 600; 
//static int img_height;
//static int img_width; 



GLOBAL(unsigned int )
imread_gray(char * filename, unsigned int ***img_Matrix);

void image_allocate(unsigned int ***img){
	*img = (unsigned int**) malloc (sizeof(unsigned int*)*img_height);				
	for (int i = 0; i < img_width; i++) 	
		(*img)[i] = (unsigned int *) malloc (sizeof(unsigned int)*img_width);	
//	for (int i = 0; i < img_height; i++) 	
//	{	for (int j = 0; j < img_width; j++) 	
//			(*img)[i][j] = i;
//	}
	
}

int print_Matrix(unsigned int  ** img);

int main(int argc, char* argv[]){
//	unsigned int** a;

	
	/**************************************************************************/
	// DeleteAfterUse
//	unsigned int img[img_height][img_width];
//	unsigned int **img_Matrix = (unsigned int **)img;
//
//	for (int i = 0; i < img_height; i++)
//	{
//		for (int j = 0; j < img_width; j++)
//		{
//			printf(" %3u ",img[0][0] = i+j);
//		} 
//			printf("\n");
//	}
	/**************************************************************************/
//	a = imread_gray(argv[1]);

	unsigned int **img_Matrix; 
	unsigned int **img;

	image_allocate(&img_Matrix);
	imread_gray(argv[1],&img_Matrix);
//	printf(" %3u ",*(*(img_Matrix)));

	free(img_Matrix);
//	image_allocate(&img);
	print_Matrix(img_Matrix);
	return 0;
}

//GLOBAL(unsigned int ** )
//imread_gray(char * filename) 
GLOBAL(unsigned int )
imread_gray(char * filename, unsigned int ***img_Matrix)
{
  struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr err;

	cinfo.err = jpeg_std_error( &err );
  /* More stuff */
  FILE * infile;		/* source file */
//  JSAMPARRAY buffer;		/* Output row buffer */
  int row_stride;		/* physical row width in output buffer */

  if ((infile = fopen(filename, "rb")) == NULL) {
    fprintf(stderr, "can't open %s\n", filename);
    return 0;
  }
  /* Step 1: allocate and initialize JPEG decompression object */

  /* Now we can initialize the JPEG decompression object. */
  jpeg_create_decompress(&cinfo); // initialize JPEG decompression

  /* Step 2: specify data source (eg, a file) */

  jpeg_stdio_src(&cinfo, infile);

  /* Step 3: read file parameters with jpeg_read_header() */

  (void) jpeg_read_header(&cinfo, TRUE); // Nötig?

  /* Step 4: set parameters for decompression */


  /* Step 5: Start decompressor */

  (void) jpeg_start_decompress(&cinfo);

  /* JSAMPLEs per row in output buffer */
  row_stride = cinfo.output_width * cinfo.output_components;
	
	/* Initializiert */
	img_width = cinfo.output_width;
	img_height = cinfo.output_height;
	int numChannels = cinfo.num_components;
	unsigned long dataSize = img_width*img_height*numChannels;
	
	unsigned char* data = (unsigned char*) malloc(dataSize);
	unsigned char* rowptr;
	

	/**************************************************************************/
//	// DeleteAfterUse
//		/*
//		 * Holt Speicher für das Bild
//		 */
//	
//		//unsigned int** img_Matrix;
//	  if ((img_Matrix) == NULL) {
//	    fprintf(stderr, " not alloc: img_Matrix");
//	    return 0;
//	  }
//	
//		*img_Matrix = (unsigned int**)malloc(sizeof(unsigned int*)*img_height ); 
//	
//	  if ((*img_Matrix) == NULL) {
//	    fprintf(stderr, " not alloc: img_Matrix_ptr");
//	    return 0;
//	  }
	/**************************************************************************/
//image_allocate(img_Matrix);	
	while (cinfo.output_scanline < img_height)
	{
		rowptr = data + cinfo.output_scanline*img_width*numChannels;		
		jpeg_read_scanlines(&cinfo,&rowptr,1);
		
	/* 
	 * Initializiert das Bild
	 */ 

		/**************************************************************************/
		// DeleteAfterUse
//		(*img_Matrix)[cinfo.output_scanline] = (unsigned int*) malloc(sizeof(unsigned int)*img_width+200); 
		/**************************************************************************/

		double helpvar = 0;
		for (int j = 0; j < img_width*numChannels; j++)
		{
			helpvar += 0.33*rowptr[j];

			if ((j+1)%3 == 0)	
			{
			(*img_Matrix)[cinfo.output_scanline-1][(j+1)/3-1] = helpvar;
			helpvar = 0;
			}
		}
	}
	 

  /* Step 7: Finish decompression */

  (void) jpeg_finish_decompress(&cinfo);

  /* Step 8: Release JPEG decompression object */

  /* This is an important step since it will release a good deal of memory. */
  jpeg_destroy_decompress(&cinfo);

  fclose(infile);

  /* And we're done! */

//		return img_Matrix;
//	printf(" %3u ",*(*(*(img_Matrix))));
	(*img_Matrix)[8][9] = 1;
		return 1;
}

int print_Matrix(unsigned int **img){
//  if (img == NULL) {
//    fprintf(stderr, " not alloc: img_Matrix to print \n");
//    return 0;
//  }
	
	for (int i = 0; i < img_height; i++)
	{
		for (int j = 0; j < img_width; j++)
		{
			printf(" %3u ",img[i][j]);
		} 
			printf("\n");
	}
	return 1;
}
