jpgin: 
	ghc --make -no-hs-main -optc-O A_jpgIn_with_Haskell.c -ljpeg -o A_jpgin

jpgout: 
	ghc --make -no-hs-main -optc-O A_jpgOut_with_Haskell.c -ljpeg -o A_jpgout

hs: *.hs
	ghc A_ImageProcess.hs
	rm -f *.{o,hi}

clean: 
	rm -rf *.{o,hi} 
	rm -f rmThisBuffer
	rm -f rmNow
	rm -f A_ImageProcess

cleana: 
	rm -rf *.{o,hi} 
	rm -rf A_jpgin A_jpgout

run:
	./0run.sh lena_testbild.jpg RmWorkedOnwithHaskell.jpg 
	open RmWorkedOnwithHaskell.jpg
	$(open -a /Applications/Google Chrome.app/ RmWorkedOnwithHaskell.jpg)
