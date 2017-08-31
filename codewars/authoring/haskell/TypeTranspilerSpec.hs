{-# LANGUAGE ApplicativeDo #-}

module TypeTranspilerSpec where

import TypeTranspiler
import Test.Hspec
import System.Random
import Control.Monad

a =>> b = transpile a `shouldBe` Right b
keep a = a =>> a

infix 2 =>>

gg a = transpile a `shouldBe` Left "Hugh?"

main :: IO ()
main = hspec $ do
  describe "simple and easy tests" $ do
    it "should work when nothing should be changed" $ do
      keep "A"
      keep "A.A"
      keep "A.A.A"
      keep "A.B.C"
      keep "A.A.A.abc.Abc"
      keep "_"
      gg "A."
      gg ">_<"
      gg ".A"
      gg ".."
      gg "123"
      gg "A.123"
    it "should work when there are generic parameters" $ do
      keep "A<A>"
      keep "B<B>"
      gg "A<>"
      gg "A<"
      "List<Int>" =>> "List<Integer>"
      gg "A>"
      "Int.Companion" =>> "Integer.Companion"
      gg "<A>"
    it "should work for star projections" $ do
      "A<*>" =>> "A<?>"
      "A<*, *, A>" =>> "A<?,?,A>"
      gg "?"
      gg "*<A>"
      gg "?<A>"
      gg "*"
      gg "A<*"
      gg "A*>"
    it "should work for variance" $ do
      "A<in A>" =>> "A<? super A>"
      "List<out T>" =>> "List<? extends T>"
      "Array<out CSharp, out Java>" =>> "Array<? extends CSharp,? extends Java>"
      "ArrayList<in out>" =>> "ArrayList<? super out>"
      "ArrayList<out in>" =>> "ArrayList<? extends in>"
      keep "A<in>"
      keep "Array<out>"
    it "should rename" $ do
      "Int" =>> "Integer"
      "List<Int>" =>> "List<Integer>"
    it "should remove spaces" $ do
      "A<A, B>" =>> "A<A,B>"
      " A " =>> "A"
      " A < A > " =>> "A<A>"
      "A  . A . B < C >" =>> "A.A.B<C>"
      gg " < > "
    it "should work when there are multiple generic parameters" $ do
      keep "A<A<A>>"
      keep "A<A<A<A<A>>>>"
      keep "A<A,B,C,D>"
      keep "A<A<A<A>,A<A<A>>>,A>"
      gg "A<A<A<A>,A<A<A>>,A>"
      gg "A<A<AA,A<A<A>>,A>"
    it "should work for 30 random tests" $ do
      let test x = keep $ "Tuple<A" ++ join (replicate x ",A") ++ ">" in
        replicateM_ 30 $ join $ test <$> randomRIO (10, 100)

  describe "complex tests" $ do
    it "should work for function types" $ do
      "(A) -> B" =>> "Function1<A,B>"
      "(A, B) -> C" =>> "Function2<A,B,C>"
      "(A<A>, B) -> C<D>" =>> "Function2<A<A>,B,C<D>>"
      "(A<A>.A<*>) -> QwQ<out T>" =>> "Function1<A<A>.A<?>,QwQ<? extends T>>"
      "(A,B,C,D,E,F,G,H) -> I" =>> "Function8<A,B,C,D,E,F,G,H,I>"
      "() -> A" =>> "Function0<A>"
      "( ) -> Abc" =>> "Function0<Abc>"
      gg "() -> ()"
      gg "(A) - > B"
      gg "() ->"
      gg "-> A"
    it "should work for complex function types" $ do
      "((A) -> B) -> C" =>> "Function1<Function1<A,B>,C>"
      "(A) -> (B) -> C" =>> "Function1<A,Function1<B,C>>"
      "(((A) -> B) -> C) -> D" =>> "Function1<Function1<Function1<A,B>,C>,D>"
      "(A, B) -> C" =>> "Function2<A,B,C>"
      "((A) -> B, (B) -> C) -> (A) -> C" =>> "Function2<Function1<A,B>,Function1<B,C>,Function1<A,C>>"
    it "should work for 30 random tests" $ do
      let test x = join (replicate x "(Int) -> ") ++ "Long" =>>
            join (replicate x "Function1<Integer,") ++ "Long" ++ replicate x '>' in
        replicateM_ 30 $ join $ test <$> randomRIO (10, 100)
    it "should work for other 30 random tests" $ do
      let test x = "(A" ++ join (replicate x ",A") ++ ")->Unit" =>>
            "Function" ++ show (x + 1) ++ "<A" ++ join (replicate x ",A") ++ ",Void>"  in
        replicateM_ 30 $ join $ test <$> randomRIO (10, 100)
--
