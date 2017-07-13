module Haskell.SylarDoom.Paintfuck where

findMatched :: Int -> String -> Int
findMatched i = f 0 $ i + 1
  where f 0 i s
          |s !! i == '[' = f 1 (i + 1) s
          |s !! i == ']' = i
          |otherwise     = f 0 (i + 1) s
        f n i s
          |s !! i == '[' = f (n + 1) (i + 1) s
          |s !! i == ']' = f (n - 1) (i + 1) s
          |otherwise     = f    n    (i + 1) s
--

flipChar :: Char -> Char
flipChar '1' = '0'
flipChar '0' = '1'

interpreter :: String -> Int -> Int -> Int -> String
interpreter   _  0 _  = []
interpreter   _  _ 0  = []
interpreter [  ] x y = initialize
interpreter code x y = undefined
  where initialize x y = take y $ repeat $ const 0 <$> [1..x]
--
