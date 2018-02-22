
run: jpeg_imread_gray.c  
	ghc --make -no-hs-main -optc-O jpeg_imread_gray.c -ljpeg -o main

clean: 
	rm -rf *.{o,hi} 
