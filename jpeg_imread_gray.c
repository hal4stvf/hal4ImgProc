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

	image_allocate(&img_Matrix);
	imread_gray(argv[1],&img_Matrix);

	write_JPEG_file("test_jpeg_grayscale.jpg",50,&img_Matrix);

	free_img(&img_Matrix);
	return 0;
}
/******************************************************************************/

