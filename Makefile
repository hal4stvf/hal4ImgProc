
run: jpeg_imread_gray.c  
	ghc --make -no-hs-main -optc-O A_jpg_with_Haskell.c -ljpeg -o A_main

clean: 
	rm -rf *.{o,hi} 
	rm rmnow.pgm	
