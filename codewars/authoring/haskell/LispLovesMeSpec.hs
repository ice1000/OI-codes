module LispLovesMeSpec where

import Control.Applicative
import Control.Monad
import Test.Hspec

import LispLovesMe

a ->> b = lispEval a `shouldBe` Just b
a =>> b = lispPretty a `shouldBe` Just b
gg a = do
  lispEval a `shouldBe` Nothing
  lispPretty a `shouldBe` Nothing
--

keep a = a =>> a

main :: IO ()
main = hspec $ do
  describe "Should parse literals" $ do
    it "should parse a single expression" $ do
      "1" ->> I32 1
      "/" ->> Sym "/"
      "boyNextDoor" ->> Sym "boyNextDoor"
      "KirisameMarisa" ->> Sym "KirisameMarisa"
      "true" ->> Boo True
      "false" ->> Boo False
      "()" ->> Nul
    it "should ignore whitespaces" $ do
      "  1,  " ->> I32 1
      "\n  null\n " ->> Nul
      "  true \n ,  \r\t" ->> Boo True
--

  describe "Should eval expressions" $ do
    it "should evaluate simple math expressions" $ do
      "(+ 1 1)" ->> I32 2
      "(* 2 2)" ->> I32 4
      "(+ 1 2 3 4 5 6 7 8 9)" ->> I32 45
      "(- 10 2 2)" ->> I32 6
      "(- 10 2 2 1)" ->> I32 5
      "(/ 100 10)" ->> I32 10
      "(/ 100 10 2)" ->> I32 5
      "(^ 2 10)" ->> I32 1024
      gg "("
      gg ")"
      gg "(/"
    it "should evaluate complex math expressions" $ do
      "(+ (+ 1 1) (+ 1 1))" ->> I32 4
      "(* (/ 10 2 5)(- 10 (* 3 3)) 100)" ->> I32 100
      "(^ 2 (+ 2 3 (* 1 5)))" ->> I32 1024
    it "should compare values" $ do
      "(> 2 1)" ->> Boo True
      "(> (+ 1 1) 1)" ->> Boo True
      "(> (+ 1 1) (+ 1 1))" ->> Boo False
      "(>= 2 1)" ->> Boo True
      "(>= (+ 1 1) 1)" ->> Boo True
      "(>= (+ 1 1) (+ 1 1))" ->> Boo True
      "(>= (+ 1 1) (+ 1 1 1))" ->> Boo False
      "(<= 2 1)" ->> Boo False
      "(<= (+ 1 1) 1)" ->> Boo False
      "(<= (+ 1 1) (+ 1 1))" ->> Boo True
      "(< 2 1)" ->> Boo False
      "(< (+ 1 1) 1)" ->> Boo False
      "(< (+ 1 1) (+ 1 1))" ->> Boo False
      "(< (+ 1 1) (+ 1 1 1))" ->> Boo True
      "(== 1 1)" ->> Boo True
      "(!= 2 2)" ->> Boo False
    it "should do boolean operations" $ do
      "(! true)" ->> Boo False
      "(! false)" ->> Boo True
      "(! (! (! (! (! (! (! true)))))))" ->> Boo False
      "(! (! (! (! (! (! (!(! (! (! (! (! (! (! true))))))))))))))" ->> Boo True
    it "should do if else" $ do
      "(if (> 2 1) 2 1)" ->> I32 2
      "(if true 2 1)" ->> I32 2
      "(if (> 2 1) 233)" ->> I32 233
      "(if (<= 2 1) 233)" ->> Nul
      "(if (! (<= 2 1)) 233)" ->> I32 233
    it "should work with lists" $ do
      "(list 1 2 3)" ->> Lst [I32 1, I32 2, I32 3]
      "(list true false null 233)" ->> Lst [Boo True, Boo False, Nul, I32 233]
      "(.. 1 100)" ->> Lst (I32 <$> [ 1 .. 100 ])
      "(.. 233 666)" ->> Lst (I32 <$> [ 233 .. 666 ])
      "(reverse (.. 1 100))" ->> Lst (I32 <$> reverse [ 1 .. 100 ])
      "(reverse (.. 233 666))" ->> Lst (I32 <$> reverse [ 233 .. 666 ])
      "(reverse (list true false null 233))" ->> Lst (reverse [Boo True, Boo False, Nul, I32 233])
      "(size (list 1 2 3))" ->> I32 3
      "(size (.. 0 1000))" ->> I32 1001

  describe "Should give errors" $ do
    it "should give errors" $ do
      "(do )" ->> Err
      "(begin ())" ->> Err
      "(shit)" ->> Err

  describe "Should pretty print" $ do
    it "should keep good codes" $ do
      keep "(+ 1 1)"
      keep "(a (b c d) e (f g h i (j k (l m) n) o) p)"
      keep "233"
    it "should reformat bad codes" $ do
      "(+  1 1)" =>> "(+ 1 1)"
      " (+  1 \t 1) " =>> "(+ 1 1)"
      " ( (a b\r)\t c ) " =>> "((a b) c)"
      " (  null  true false  )\n " =>> "(null true false)"
      " ( 1 ) " =>> "(1)"
      "(\n ( a ) \r( b) \t(c ) )" =>> "((a) (b) (c))"
--
