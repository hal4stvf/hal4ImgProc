import System.IO
import System.Environment
import Data.List

import BBRM 


-- Name der outputfiles
--imageFile = "rmHaskel.txt"
-- Hier wird das Bild in ein Textdatei kopiert 
arrayPrinter = (\s -> c ++ s) . foldr (++) "" . map (\ s -> s ++ "\n") . map (intercalate " " . map show)
  where c = (show $ length $ processImage !! 0) ++ " " ++ (show $ length processImage) ++ "\n"
main = do
 args <- getArgs
 writeFile (args !! 0) . arrayPrinter $ processImage 

--processImage = [[1,2,3],[2,3]]

