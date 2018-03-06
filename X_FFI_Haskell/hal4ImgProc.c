#include "../hal4ImgProc.h"
#include <HsFFI.h>
extern void __stginit_StvfC(void);
#include "StvfC_stub.h"
#include <stdio.h> 


int main(int argc, char* argv[]) {
 //int i = 1;
	int B[3]; 
 int* A = malloc(sizeof(int)*8);
 for (int i = 0; i < 8; i++){
 	A[i] = i+10;
}
   for (int i = 0; i < 8; i++){
	 printf("Hallo: %d\n", A[i]);	 
	 }

 /******************************************************************************/
 // Here is the call for Haskell //
 hs_init(&argc, &argv);
	 //hs_add_root(__stginit_StvfC);
	// i = testH(2);
   A = testH2(8, A);
   for (int i = 0; i < 8; i++){
	 printf("Hallo: %d\n", A[i]);	 
	 }
	 //printf("Hallo: %d\n", i);	 
 hs_exit();
 /******************************************************************************/

 return 0;	
}
