import System.IO (openFile, IOMode (ReadMode), hGetContents)
import qualified Data.Set as Set
import Data.List

main = do
    handle <- openFile "in.txt" ReadMode
    contents <- hGetContents handle
    let
        input = lines contents
        parsedInput = processInput input
        a = considerElves parsedInput 0
    print a

processInput input = Set.fromList [(i, j) | (i, row) <- zip [0..] input
                                  , (j, char) <- zip [0..] row
                                  , char == '#']

considerElf roundCount elvesSet elf =
    let
        (i, j) = elf
        [nw, n, ne,
         w,  _, e,
         sw, s, se] = [(i+a, j+b) | a <- [-1, 0, 1]
                                  , b <- [-1, 0, 1]]

        moves = any (== True) $ map (\x -> x `Set.member` elvesSet) [nw, n, ne, w, e, sw, s, se]

        directions = cycle [[n, ne, nw], [s, se, sw], [w, nw, sw], [e, ne, se]]
        directions4 = take 4 $ drop roundCount directions
        direction = dropWhile (any (== True) . map (\x -> x `Set.member` elvesSet)) directions4
    in
        if not moves || null direction then
            (False, elf)
        else
            (True, head $ head direction)

undoDuplicate [] = []
undoDuplicate changes
    | length duplicates == 1 = duplicates ++ (undoDuplicate $ tail changes)
    | otherwise              = undo ++ (undoDuplicate $ remainingchanges)
    where
        (new, _) = head changes
        duplicates = takeWhile ((== new) . fst) changes
        undo = map (\(a, b) -> (b, b)) duplicates
        remainingchanges = drop (length undo) changes

considerElves elves n
    | all (== False) moved = n+1
    | otherwise            = considerElves next (n+1)
    where
        elvesList = Set.toList elves
        (moved, nextList) = unzip $ map (considerElf n elves) elvesList
        changes' = sort $ zip nextList elvesList
        changes = undoDuplicate changes'
        next = Set.fromList $ map fst changes
