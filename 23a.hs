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
        res = emptyGround a
        -- arr = unlines $ map (intercalate "") [[if (i, j) `Set.member` a then "#" else "." | j <- [-3..10]] | i <- [-2..9]]
    -- putStr arr
    print res

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
            elf
        else
            head $ head direction

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
    | n == 10   = elves
    | otherwise = considerElves next (n+1)
    where
        elvesList = Set.toList elves
        nextList = map (considerElf n elves) elvesList
        changes' = sort $ zip nextList elvesList
        changes = undoDuplicate changes'
        next = Set.fromList $ map fst changes

emptyGround elves =
    let
        (xmin, ymin) = Set.foldl (\(a, b) (c, d) -> (min a c, min b d)) (999, 999) elves
        (xmax, ymax) = Set.foldl (\(a, b) (c, d) -> (max a c, max b d)) (0, 0) elves
    in
        (xmax - xmin + 1) * (ymax - ymin + 1) - Set.size elves