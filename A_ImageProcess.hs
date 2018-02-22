import System.IO
import System.Environment
import Data.List

--import BBRM 


-- Hier wird das Bild in ein Textdatei kopiert 
arrayPrinter = foldr (++) "" . map (\ s -> s ++ "\n") . map (intercalate " " . map show)

conv :: [String] -> [[Int]]
conv = map (map read) . map words
img :: String -> [[Int]]
img = putDimensions . imgProccessing . conv . lines 
  where putDimensions xs = [(length $ xs !! 0), length xs] : xs 


main = do
  contents <- getContents
  args <- getArgs
  writeFile (args !! 0) . arrayPrinter . img $ contents

imgProccessing :: [[Int]] -> [[Int]]
--imgProccessing  = map (map (\c -> 255))  
imgProccessing = id 

------------------------------
-- Another Version.					 |
-- Braucht compilierten Daten|
-- typ                       |
-- Do not! remove            |
------------------------------
  --where c = (show $ length $ img !! 0) ++ " " ++ (show $ length img) ++ "\n" ++ img 
-- main = do
-- args <- getArgs
-- writeFile (args !! 0) . arrayPrinter $ processImage 
--------------------------------------------------



