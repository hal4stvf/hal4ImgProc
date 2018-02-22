#!/bin/bash


echo "Bild wird zurecht gelegt und bearbeitet"
./A_jpgin "$1" | runhaskell A_ImageProcess.hs rmNow 
#echo "Bild wird bearbeitet"
#make hs
#./A_ImageProcess rmNow 

echo "Hier kommt das Bild"
./A_jpgout rmNow "$2"
make clean

