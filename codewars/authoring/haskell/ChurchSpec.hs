import Test.Hspec
import System.Random

import Prelude hiding (succ)
import Church

turn :: Int -> Number
turn 0 = zero
turn n = succ $ turn (n - 1)

randomList :: Int -> Int -> IO [Int]
randomList a b = getStdGen >>= return . randomRs (a, b)

getRand :: Int -> IO [Int]
getRand n = take n <$> randomList 233 666

runTest (a1, b1) = let a = mod a1 15 in
                   let b = mod b1 5 in do
  eval (turn a + turn b) `shouldBe` (toInteger $ a + b)
  eval (turn a * turn b) `shouldBe` (toInteger $ a * b)
  eval (turn a `pow` turn b) `shouldBe` (toInteger $ a ^ b)
--

main :: IO ()
main = hspec $ do
  describe "when using Chruch numbers" $ do
    it "1 + 0 equals 1" $ do
      eval (one + zero) `shouldBe` 1
    it "2 * 2 equals 4" $ do
      eval (succ one * succ one) `shouldBe` 4
    it "2 `pow` 3 equals 8" $ do
      eval (succ one `pow` succ (succ one)) `shouldBe` 8
    it "2 + 3 equals 5" $ do
      eval (two + three) `shouldBe` 5
    it "3 * 2 equals 6" $ do
      eval (three * two) `shouldBe` 6
    it "3 `pow` 2 equals 9" $ do
      eval (3 `pow` 2) `shouldBe` 9
    it "random tests" $ do
      rand1 <- getRand 100
      rand2 <- getRand 100
      head (runTest <$> zip rand1 rand2)
--

