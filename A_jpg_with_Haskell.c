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

	unsigned char **img_Matrix; 
	FILE *pOut = fopen("rmnow.pgm","a");

	image_allocate(&img_Matrix);
	imread_gray(argv[1],&img_Matrix);

	write_PGM_file(img_Matrix,pOut);
	write_JPEG_file("test_jpeg_grayscale.jpg",50,&img_Matrix);

	free_img(&img_Matrix);
	fclose(pOut);
	return 0;
}
/******************************************************************************/

