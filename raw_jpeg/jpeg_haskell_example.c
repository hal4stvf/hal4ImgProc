/* example code that will eventually show how to work with haskell 
 * functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jpeglib.h"
#include "hal4ImgProc.h"

#include <setjmp.h> // nicht nötig, oder?

/* Dies bauchen wir für Haskell.
 * Wichtig: die C Datei muss nun mit ghc compiliert werden. 
 * Der Befehl sind dann auf unix envoirements so aus:
 * 	ghc --make -no-hs-main -optc-O [name].c [Haskellfile] [linker] -o [Programmn]
 * zuvor müsst ihr eure haskell datei so compilieren:
 * 	ghc -c -O [Haskellfile].hs
*/

#include "HsFFI.h"



/******************************************************************************/
int main(int argc, char* argv[]){
/* Haskell wird initialisiert */
hs_init(&argc, &argv);

	unsigned char **img_Matrix; 

	image_allocate(&img_Matrix);
	imread_gray(argv[1],&img_Matrix);

	img_Matrix = zeros_hs(img_Matrix);		

	write_JPEG_file("test_jpeg_grayscale.jpg",50,&img_Matrix);
	free_img(&img_Matrix);

	/* Haskell wird geschlossen */
	hs_exit();
	return 0;
}
/******************************************************************************/

