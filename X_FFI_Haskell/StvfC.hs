module StvfC where

{-
 - This should be a function
 - that I can call in C 
 - which than will do my ImageProcessing.
 - VERY BAD VERSION!!! UNSAFE
 -}

import Foreign.Ptr
import Foreign.C.Types
import Foreign.Marshal.Array
import System.IO
import Foreign
import System.IO.Unsafe

-- Eigentlich Bildverarbeitung
imgProc :: [[Int]] -> [[Int]]
--imgProc = map (map (\a -> a+1)) 
--imgProc = map (map (id)) 
imgProc = id
--imgProc xss = [[ 0 | x <-xs] | xs <- xss] 
--imgProc xss = [[ if x >= 150 then 1 else 0 | x <-xs] | xs <- xss] 

-- Umrechnen
test2 :: Int -> Int -> [CInt] -> [Int]
test2 n m = revConvul . imgProc . (convul n ) . (map fromIntegral)

-- Bild in 2d überführen
convul :: Int -> [Int] -> [[Int]]
convul _ [] = []
convul n img = [take n img] ++ convul n (drop n img) 

-- Bild wieder in 1d überführen
revConvul :: [[Int]] -> [Int]
revConvul = foldr (++) []

-- Umschreiben für C
testH2 :: Int -> Int -> Ptr CInt ->  IO (Ptr CInt)
testH2 n m img = newArray $ (map fromIntegral) $ unsafePerformIO $ fmap (test2 n m) $ peekArray (n*m) img

-- Exportiert den ganzen Spaß
foreign export ccall testH2 :: Int -> Int -> Ptr CInt -> IO (Ptr CInt) 

{-
foreign export ccall testH2 :: Int -> Int -> Ptr CInt -> IO (Ptr CInt) 
testH2 n m = newArray . unsafePerformIO . peekArray (n*m)
-}
