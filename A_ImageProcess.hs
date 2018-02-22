import System.IO
import System.Environment
import Data.List


-- Name der outputfiles
--imageFile = "rmHaskel.txt"
-- Hier wird das Bild in ein Textdatei kopiert 
arrayPrinter = foldr (++) "" . map (\ s -> s ++ "\n") . map (intercalate " " . map show)
main = do
 args <- getArgs
 writeFile (args !! 0) . arrayPrinter $ processImage 

processImage = [[1,2,3],[2,3]]

