import Data.List.Split
import System.IO (openFile, IOMode (ReadMode), hGetContents)

main = do
    handle <- openFile "in.txt" ReadMode
    contents <- hGetContents handle
    let
        input = lines contents
        result = calcResult $ processInput input
    print result

processInput input =
    let
        pairs = map (splitOn ",") input
        sections = (map . map) (splitOn "-") pairs
        intpairs = (map . map . map) read sections :: [[[Integer]]]
    in
        intpairs

calcResult :: [[[Integer]]] -> Integer
calcResult [] = 0
calcResult pairs
    | a2 < b1 || b2 < a1 = calcResult (tail pairs)
    | otherwise = 1 + calcResult (tail pairs)
    where
        pair = head pairs
        pair1 = head pair
        pair2 = last pair
        a1 = head pair1
        a2 = last pair1
        b1 = head pair2
        b2 = last pair2
