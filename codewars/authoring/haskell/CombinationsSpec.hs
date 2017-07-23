module CombinationSpec where

import Test.Hspec
import Combinations
import Data.List (tails, sort)
import Test.QuickCheck

-- combinations :: Int -> [a] -> [[a]]
-- combinations = undefined

(~~) a b = f a `shouldBe` f b where
  f = sort . fmap sort

main :: IO ()
main = hspec $ do
  describe "Testing combinations" $ do
    it "should work for examples" $ do
      combinations 0 [1..5] ~~ [[]]
      combinations 1 [1..5] ~~ [[1],[2],[3],[4],[5]]
      combinations 2 [1..5] ~~ [[1,2],[1,3],[1,4],[1,5],[2,3],[2,4],[2,5],[3,4],[3,5],[4,5]]
      combinations 3 [1..5] ~~ [[1,2,3],[1,2,4],[1,2,5],[1,3,4],[1,3,5],[1,4,5],[2,3,4],[2,3,5],[2,4,5],[3,4,5]]
      combinations 4 [1..5] ~~ [[1,2,3,4],[1,2,3,5],[1,2,4,5],[1,3,4,5],[2,3,4,5]]
      combinations 5 [1..5] ~~ [[1,2,3,4,5]]
    it "randomized testing with integers" $ property $ \n -> forAll (resize 10 arbitrary) $ \xs->
      combinations (p xs n) xs ~~ combinations' (p xs n) (xs :: [Integer])
    it "should work for polymorphic list" $ property $ \n -> forAll (resize 10 arbitrary) $ \xs ->
      combinations n xs ~~ combinations' n (xs :: [()])
--

p :: [a] -> Int -> Int
p [] _ = 0
p xs n = ((1 + abs n) `mod` length xs)

combinations' :: Int -> [a] -> [[a]]
combinations' n xs =
  case n of
    0 -> [[]]
    _ -> [ y : ys | y : xs' <- tails xs, ys <- combinations' (n - 1) xs' ]
--
