
run: 
	ghc --make -no-hs-main -optc-O hal4ImgProc.c StvfC -ljpeg -o hal4ImgProcs
	ghc -c -O StvfC.hs
	##./hal4ImgProcs RmWorkedOnwithHaskell.jpg
	./hal4ImgProcs testthis.jpg
	

hs: Stvfc.hs	
	ghc -c -O StvfC.hs

clean:
	rm -rf *.o *.hi
	rm hal4ImgProcs

debug:
	ghc --make -no-hs-main -optc-O -debug hal4ImgProc.c StvfC -ljpeg -o hal4ImgProcs
	
#	ghc --make -no-hs-main -optc-O -g hal4ImgProcHs.h StvfC -ljpeg -o hal4ImgProcs
