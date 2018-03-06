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
--import Foreign.C.Types

-- Eigentlich Bildverarbeitung
test2 :: [Int] -> [Int]
test2 = map (\a -> 3)

-- Umschreiben für C
testH2 :: Int -> Ptr CInt ->  IO (Ptr CInt)
testH2 m img = newArray $ (map fromIntegral) $ unsafePerformIO $ fmap (test2 . (map fromIntegral)) $ peekArray m img

-- Exportiert den ganzen Spaß
foreign export ccall testH2 :: Int -> Ptr CInt -> IO (Ptr CInt) 



