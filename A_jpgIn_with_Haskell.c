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

	/* Convertiert die Datei in Graustufen. */
	imread_gray(argv[1],&img_Matrix);
	/* Druckt die Matrix auf den Bildschirm. Kann dann "gepipt" werden.*/
	print_Matrix(img_Matrix);

	free_img(&img_Matrix);
	return 0;
}
/******************************************************************************/
