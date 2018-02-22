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
	FILE *pOut;
	if (argc < 3){
		pOut = fopen("BBRM.hs","w");
	}
	else {
	 pOut = fopen(argv[2],"w");
	}
	/* hier muss in einem shell Skript als argv noch mithilfe von
	 * convert die Größe des Bildes übergeben werden.
	 * Funktioniert zur Zeit auch so, solange das Bilder kleiner
	 * als 600x600 ist.*/
	//int w = 0;
	//int h = 0;

	//image_allocate(w,h,&img_Matrix);
	imread_gray(argv[1],&img_Matrix);

	write_Haskell_file(img_Matrix,pOut);
	//write_JPEG_file("test_jpeg_grayscale.jpg",50,&img_Matrix);

	free_img(&img_Matrix);
	fclose(pOut);
	return 0;
}
/******************************************************************************/
