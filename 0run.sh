#!/bin/bash


echo "Bild wird zurecht gelegt und bearbeitet"
# Falls mit pipes gearbeitet werden soll.
#./A_jpgin "$1" | runhaskell A_ImageProcess.hs rmNow 
#./A_jpgin "$1" | ./A_ImageProcess rmNow 

# Falls es schneller ist in eine Datei zu schreiben.
./A_jpgin "$1"  
make hs
./A_ImageProcess rmNow 
#echo "Bild wird bearbeitet"

echo "Hier kommt das Bild"
./A_jpgout rmNow "$2"
make clean

