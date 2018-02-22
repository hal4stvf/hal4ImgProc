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
//	if (argc < 3){
		pOut = fopen("rmThisBuffer","w");
//	}
//	else {
//	 pOut = fopen(argv[2],"w");
//	}
	imread_gray(argv[1],&img_Matrix);

//	write_Haskell_file(img_Matrix,pOut);
//	print_Matrix(img_Matrix);
		write_PGM_file(img_Matrix, pOut);

	free_img(&img_Matrix);
	fclose(pOut);
	return 0;
}
/******************************************************************************/
