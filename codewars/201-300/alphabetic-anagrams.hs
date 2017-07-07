module AlphabeticAnagrams where

import Data.List
import Data.Bits
import Control.Arrow
import Data.Maybe

alpha = ['A'..'Z']

type BIT = [Int]

mapString :: String -> [Int]
mapString = ((\x -> fromJust $ elemIndex x alpha) <$>)

lowbit :: Int -> Int
lowbit n = n .&. (-n)

bitSum :: [Int] -> Int -> Int
bitSum bit 0 = 0
bitSum bit x = (bit !! x) + (bitSum bit $ x - lowbit x)

-- bitAdd :: [Int] -> Int -> Int -> [Int]
-- bitAdd bit l i
--   |i > l     = bit
--   |otherwise = bitAdd (update bit l l i) (i + lowbit i)
--

inv :: Ord a => [a] -> [(a, a)]
inv xs = [(a, b) | (a : bs) <- tails xs, b <- bs, a > b]

-- lexiPos :: String -> Integer
-- lexiPos s = toInteger $ 1 + (length $ inv $ mapString s)

lexiPos :: String -> Integer
lexiPos [x] = 1
lexiPos w@(c:cs) = sum (f <$> ys) + lexiPos cs
    where hshs = tail . init . tails $ w
          tsts = init . tail . inits $ w
          func i (h : t) = h : i ++ t
          ys = nub . ((sort . tail) <$>) . filter ((< c) . head) . zipWith func tsts $ hshs
          f = uncurry div . (g . sum &&& product . (g <$>)) . (length <$>) . group . sort
--
