#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StvfC_stub.h"

#include "jpeglib.h"

#include <setjmp.h> // nicht nötig, oder?

/******************************************************************************
*******************************************************************************
******************************************************************************/

/* 
*  [TODO] hier noch die höhe und breite des Bildes dynamisch einbauen
*/

/*
int img_height = 600;
int img_width = 600; 
*/
int img_height; 
int img_width; 

GLOBAL(int)
imread_gray(char * filename, unsigned char ***img_Matrix);

GLOBAL(void)
write_JPEG_file (char * filename, int quality, unsigned char *** img_ptr);

GLOBAL(int)
improcessGray (char* filename, unsigned char ***img_Matrix, int imgProc);

int image_allocate(int w, int h, unsigned char ***img);

void free_img(unsigned char ***img);

int print_Matrix(unsigned char **img);

int write_PGM_file (unsigned char ** img, FILE *pOutputfile);

int write_Haskell_file (unsigned char ** img, FILE *pOutputfile);

int read_to_img(int width, int height, unsigned char *** img, FILE *pInput);

void img2dto1d(unsigned char** img_M, int** pIm, int n,int m);
void img2dto1d(unsigned char** img_M, int** pIm, int n,int m){
	for (int i = 0; i < n ; i++){
			for(int j = 0; j < m; j++){
		    (*pIm)[j+i*m] = (int)img_M[i][j];	 	
				}
		}	
	}

void img1dto2d(unsigned char*** img_Matrix, int* pImg, int n, int m);
void img1dto2d(unsigned char*** img_Matrix, int* pImg, int n, int m){
	for (int i = 0; i < n ; i++){
		for(int j = 0; j < m; j++){
	   (*img_Matrix)[i][j] = (unsigned char)pImg[m*i+j];	 	
	 	}
	}	
}

/******************************************************************************
******************************************************************************/

/* [Purpose] imread_gray Function. 
*	it takes in a Filename and Pointer to a Pointer of Pointer of unsigned char**
*	It decompresses the jpeg associated with the filename and puts it in grayscale
*/

GLOBAL(int) // Wofür das GLOBAL?
imread_gray(char * filename, unsigned char ***img_Matrix)
{
  struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr err;

	cinfo.err = jpeg_std_error( &err );
  /* More stuff */
  FILE * infile;		/* source file */
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
	image_allocate(img_width,img_height,img_Matrix);	
	while (cinfo.output_scanline < img_height)
	{
		rowptr = data + cinfo.output_scanline*img_width*numChannels;		
		jpeg_read_scanlines(&cinfo,&rowptr,1);
		
	/* 
	 * Initializiert das Bild
	 */ 

		if (numChannels != 1){
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
		else {
			for (int j = 0; j < img_width; j++)
			{
				(*img_Matrix)[cinfo.output_scanline-1][j] = rowptr[j];
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
	return 1;
}

/******************************************************************************/


/* [Purpose] Will compress a processed image to jpeg.
*/

GLOBAL(void)
write_JPEG_file (char * filename, int quality, unsigned char *** img_ptr)
{
  /* This struct contains the JPEG compression parameters and pointers to
   */

  struct jpeg_compress_struct cinfo;

  /* This struct represents a JPEG error handler.
   */

  struct jpeg_error_mgr jerr;

  /* More stuff */

  FILE * outfile;		/* target file */
  JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
  int row_stride;		/* physical row width in image buffer */

  /* Step 1: allocate and initialize JPEG compression object */

  cinfo.err = jpeg_std_error(&jerr);

  /* Now we can initialize the JPEG compression object. */

  jpeg_create_compress(&cinfo);

  /* Step 2: specify data destination (eg, a file) */

  if ((outfile = fopen(filename, "wb")) == NULL) {
    fprintf(stderr, "can't open %s\n", filename);
    exit(1);
  }

  jpeg_stdio_dest(&cinfo, outfile);

  /* Step 3: set parameters for compression */

  /* First we supply a description of the input image.
   * Four fields of the cinfo struct must be filled in:
   */

  cinfo.image_width = img_width; 	/* image width and height, in pixels */
  cinfo.image_height = img_height;
  cinfo.input_components = 1;		/* # of color components per pixel */
  cinfo.in_color_space = JCS_GRAYSCALE; 	/* colorspace of input image */
  /* Now use the library's routine to set default compression parameters.
   */
  jpeg_set_defaults(&cinfo);
  /* Now you can set any non-default parameters you wish to.
   * Here we just illustrate the use of quality (quantization table) scaling:
   */
  jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);

  /* Step 4: Start compressor */

  jpeg_start_compress(&cinfo, TRUE);

  /* Step 5: while (scan lines remain to be written) */
  /*           jpeg_write_scanlines(...); */

  row_stride = img_width;	/* JSAMPLEs per row in image_buffer */

  while (cinfo.next_scanline < cinfo.image_height) {
    /* jpeg_write_scanlines expects an array of pointers to scanlines.
     * Here the array is only one element long, but you could pass
     * more than one scanline at a time if that's more convenient.
     */
    row_pointer[0] = (*img_ptr)[cinfo.next_scanline];
    (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }

  /* Step 6: Finish compression */

  jpeg_finish_compress(&cinfo);
  /* After finish_compress, we can close the output file. */
  fclose(outfile);

  /* Step 7: release JPEG compression object */

  /* This is an important step since it will release a good deal of memory. */
  jpeg_destroy_compress(&cinfo);

  /* And we're done! */
}

/******************************************************************************/
/* [Purpose] of 
 * Liest ein Bild ein, macht etwas ausgewählt mit int. 
 */

GLOBAL(int)
improcessGray(char* filename, unsigned char ***img_Matrix, int imgProc){

 imread_gray(filename, img_Matrix);

	/**** ab hier Haskell ****/

	// Holt den Speicherplatz  für ein 1D Bild
	int* pImg = malloc(sizeof(int)*img_width*img_height);

	// Konvertiert das Bild in 1D
	img2dto1d(*img_Matrix, &pImg, img_width, img_height);
	
	// Wendet Haskell an
	// Hier muss dann je nach Zahl oder int ein anderes Programm laufen
	pImg = testH2(img_width, img_height, pImg);	

	// Konvertiert das Bild wieder zu 2d	
	img1dto2d(img_Matrix, pImg, img_width, img_height);

	// Gibt das 1d wieder frei
  free(pImg);

  /* And we're done! */
	return 1;
	
	}

/******************************************************************************/
/* [Purpose] of print Matrix
 * Funktion um die Matrix auf die Konsole ausgibt
 */

int print_Matrix(unsigned char **img){

	/* Is there something to print? */

  if (img == NULL) {
    fprintf(stderr, " not alloc: img_Matrix to print \n");
    return 0;
  }
	//////////////////////////////////////////////////////////////////////////////

	/* Prints the Matrix to the display */	

	for (int i = 0; i < img_height; i++)
	{
		for (int j = 0; j < img_width; j++)
		{
			printf(" %3u ",img[i][j]);
		} 
			printf("\n");
	}
	//////////////////////////////////////////////////////////////////////////////
	return 0;
}
/******************************************************************************/
/* [Purpose] of write PGM Matrix
 * Funktion um die Matrix in ein textDatei zu schreiben
 */

int write_PGM_file(unsigned char **img, FILE *pOutputfile){

	/* Is there something to print? */

  if (img == NULL) {
    fprintf(stderr, " not alloc: img_Matrix to print \n");
    return 0;
  }
	//////////////////////////////////////////////////////////////////////////////

	/* Prints the Matrix to the file*/	

	for (int i = 0; i < img_height; i++)
	{
		for (int j = 0; j < img_width; j++)
		{
			fprintf(pOutputfile,"%3u ",img[i][j]);
		} 
			fprintf(pOutputfile,"\n");
	}
	//////////////////////////////////////////////////////////////////////////////
	return 0;
}
/******************************************************************************/
/* [Purpose] of write Haskell Matrix
 * Funktion um die Matrix in eine Haskell Datei zu schreiben
 */

int write_Haskell_file(unsigned char **img, FILE *pOutputfile){

	/* Is there something to print? */

  if (img == NULL) {
    fprintf(stderr, " not alloc: img_Matrix to print \n");
    return 0;
  }
	//////////////////////////////////////////////////////////////////////////////

	/* Prints the Matrix to a Haskell file*/	

	fprintf(pOutputfile,"module BBRM where \n");
	fprintf(pOutputfile,"processImage :: [[Int]]\n");
	fprintf(pOutputfile,"processImage = [");
	for (int i = 0; i < img_height; i++)
	{
		fprintf(pOutputfile,"[");
		for (int j = 0; j < img_width; j++)
		{
			if (j != img_width-1)
			fprintf(pOutputfile,"%3u,",img[i][j]);
			else 
			fprintf(pOutputfile,"%3u",img[i][j]);
		} 
			if (i != img_height -1)
			fprintf(pOutputfile,"],");
			else
			fprintf(pOutputfile,"]");
			
	}
	fprintf(pOutputfile,"]");
	//////////////////////////////////////////////////////////////////////////////
	return 0;
}
/******************************************************************************/
/* [Purpose] 
*/
int image_allocate(int w, int h,unsigned char ***img){
	/* Erstmal, weil jpgin noch nicht dynamisch denkt.*/
	if (w == 0){
	w = img_width;
	h = img_height;
		}
	*img = (unsigned char**) malloc (sizeof(unsigned char*)*h);				
	for (int i = 0; i < h; i++){ 	
		(*img)[i] = (unsigned char *) malloc (sizeof(unsigned char)*w);	
	}
	return 0;
}
/******************************************************************************/

/* [Purpose] 
*/
void free_img(unsigned char *** img)
{
	for(int i = 0; i < img_width; i++)
		free((*img)[i]);

	free(*img);
}
/******************************************************************************/
/* [Purpose] 
* liest haskell Dateiausgabe in ein Bild ein.
*/
int read_to_img(int width, int height, unsigned char *** img, FILE *pInput){
	int c;

 /* Initializiere das Bild */	
 for (int i = 0; i < height; i++){
	for (int j = 0; j < width; j++){
			fscanf(pInput, "%d", &c);
			(*img)[i][j] = c;
		} 
	 }
return 0;		
}
