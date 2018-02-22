jpgin: 
	ghc --make -no-hs-main -optc-O A_jpgIn_with_Haskell.c -ljpeg -o A_jpgin

jpgout: 
	ghc --make -no-hs-main -optc-O A_jpgOut_with_Haskell.c -ljpeg -o A_jpgout

hs:
	ghc A_ImageProcess.hs

clean: 
	rm -rf *.{o,hi} 
	rm -f rmNow
	rm -f A_ImageProcess

cleana: 
	rm -rf *.{o,hi} 
	rm -rf A_jpgin A_jpgout

run:
	make jpgin
	make jpgout
	make clean
