jpgin: 
	ghc --make -no-hs-main -optc-O A_jpgIn_with_Haskell.c -ljpeg -o A_jpgin

jpgout: 
	ghc --make -no-hs-main -optc-O A_jpgOut_with_Haskell.c -ljpeg -o A_jpgout

clean: 
	rm -rf *.{o,hi} 
	rm rmnow.pgm	

cleana: 
	rm -rf *.{o,hi} 
	rm rmnow.pgm	
	rm A_jpgin jpgout
