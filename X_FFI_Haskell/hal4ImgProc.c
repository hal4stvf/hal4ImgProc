#include "hal4ImgProcHs.h"
//#include "../hal4ImgProc.h"
#include <HsFFI.h>
//extern void __stginit_StvfC(void);
#include "StvfC_stub.h"
#include <stdio.h> 


int main(int argc, char* argv[]) {
	unsigned char **img_Matrix; 
	FILE *pOut;

 /******************************************************************************/
 // Here is the call for Haskell //
 hs_init(&argc, &argv);
 
	 // Not used CODE // hs_add_root(__stginit_StvfC); // Wofür??

 // Here the img will be decoded
 // and haskell programm (1) is called.
 improcessGray(argv[1],&img_Matrix,1);

 // Writes the worked on image to test.jpg
 write_JPEG_file ("test.jpg", 50, &img_Matrix);

 free_img(&img_Matrix);
 fclose(pOut);

 hs_exit();
 /******************************************************************************/

 return 0;	
}

