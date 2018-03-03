module StvfC where

import Foreign
import Foreign.C.Types
-- 
-- fibonacci :: Int -> Int
-- fibonacci n = fibs !! n
--   where fibs = 0 : 1 : zipWith (+) fibs (tail fibs)
-- 
-- fibonacci_hs :: CInt -> CInt
-- fibonacci_hs = fromIntegral . fibonacci . fromIntegral 
-- 
-- foreign export ccall fibonacci_hs :: CInt -> CInt

  zeros :: [[Int]] -> [[Int]]
  zeros xss = [[0 | x <-xs] | xs <- xss]
  
  foreign export ccall zeros_hs :: [[CInt]] -> [[CInt]]

