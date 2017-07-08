module Manhattan where

manhattanDistance :: (Int, Int) -> (Int, Int) -> Int
manhattanDistance (a, b) (c, d) = abs (a - c) + abs (b - d)
