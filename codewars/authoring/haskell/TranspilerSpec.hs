module TranspilerTest where

import Transpiler (transpile)
import Test.Hspec

s =>> c = transpile s `shouldBe` Left c
gg s = transpile s `shouldBe` Right "Hugh?"

main :: IO ()
main = hspec $ do
  describe "When there's no lambda" $ do
    it "Should work when expressions are very simple" $ do
      "call()" =>> "call()"
      "callFunc(a)" =>> "callFunc(a)"
      "callFunc(123)" =>> "callFunc(123)"
      "func(jjfly)" =>> "func(jjfly)"
    it "Should not parse wtf" $ do
      gg "%^&*("
      gg "x9x92xb29xub29bx120()!("
    it "Should work when there're lots of spaces" $ do
      "invoke  (       a    ,   b   )" =>> "invoke(a,b)"
      "gg     (  a  )  " =>> "gg(a)"
      "shit                (                 )   " =>> "shit()"
    it "Should work when there're multiple parameters" $ do
      "invoke(a, b)" =>> "invoke(a,b)"
      "invoke(a, 1, b, 2)" =>> "invoke(a,1,b,2)"
      "invoke(a, 1,b, 2)" =>> "invoke(a,1,b,2)"
      "i(123,abc,bsa,xsa)" =>> "i(123,abc,bsa,xsa)"
      gg "f(a,)"
      gg "f("
      gg ")"
      gg "f (,a)"

  describe "When there're lambda expressions" $ do
    it "Should work for simple tests" $ do
      "call({})" =>> "call((){})"
      "invoke({},{})" =>> "invoke((){},(){})"
      "invoke({},{},{},{},{},{},{},{},{},{})" =>> "invoke((){},(){},(){},(){},(){},(){},(){},(){},(){},(){})"
      gg "i(,{})"
    it "Should work for lambdas with single paramter" $ do
      "f({a->})" =>> "f((a){})"
      "f({_->})" =>> "f((_){})"
      "f({assWeCan->})" =>> "f((assWeCan){})"
      gg "f({a->)"
      gg "f(a->})"
      gg "f({1a->a})"
    it "Should work when lambda has an expression inside" $ do
      "f({a->a})" =>> "f((a){a;})"
      "f({jj->assWeCan})" =>> "f((jj){assWeCan;})"
      gg "f(->)"

  describe "When lambda expressions aren't inside brackets" $ do
    it "Should work for empty lambdas" $ do
      "call(\n){}" =>> "call((){})"
      "call{}" =>> "call((){})"
      "inv( a) { }" =>> "inv(a,(){})"
      "invo(123, abc ) { } " =>> "invo(123,abc,(){})"
    it "Should work when there're lots of spaces" $ do
      "invoke  (       a    ,   b   ) { } " =>> "invoke(a,b,(){})"
      "gg     (  a  ) {  } " =>> "gg(a,(){})"
      "shit                (                 )   " =>> "shit()"
    it "Should work when there're parameters" $ do
      "f(x){a->}" =>> "f(x,(a){})"
      "f{a->}" =>> "f((a){})"
      "f(q){abc->}" =>> "f(q,(abc){})"
      "f{a,b->}" =>> "f((a,b){})"
      "f(){a,b->}" =>> "f((a,b){})"
      "f(){a,b,c,d->}" =>> "f((a,b,c,d){})"
      "f(x,y){a,b,c,d->}" =>> "f(x,y,(a,b,c,d){})"
      gg "f(){->a}"
    it "Should work when there's a statement inside lambda" $ do
      "f(a,b){a->a}" =>> "f(a,b,(a){a;})"
      "f(x,y){a,b->a \nb}" =>> "f(x,y,(a,b){a;b;})"
      "f(abc,def){a,b,c,d,e->a\n  b\n c\n d\n e}" =>> "f(abc,def,(a,b,c,d,e){a;b;c;d;e;})"
      gg "run{->a}"
    it "Should work when there're no parameters but statements" $ do
      "run{a}" =>> "run((){a;})"
      "run(a){ass}" =>> "run(a,(){ass;})"
      "run(a){ass we can}" =>> "run(a,(){ass;we;can;})"

  describe "When invoking a lambda directly" $ do
    it "Should work when it's bare" $ do
      "{}()" =>> "(){}()"
      "{a}()" =>> "(){a;}()"
    it "Should work when there're parameters" $ do
      "{a->a}(233)" =>> "(a){a;}(233)"
      "{a,b,c->a  b c}(233,666,999)" =>> "(a,b,c){a;b;c;}(233,666,999)"
      "{a,b,c->a  b c }  (233 , 666, 999)" =>> "(a,b,c){a;b;c;}(233,666,999)"
--
