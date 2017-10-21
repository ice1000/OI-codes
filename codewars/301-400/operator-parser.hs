{-# LANGUAGE DeriveFunctor #-}
{-# LANGUAGE FlexibleContexts #-}

module OperatorParser
    ( OpTree(..)
    , Associativity(..)
    , op
    , foldTree
    , parseOperators
    , module Text.ParserCombinators.ReadP
    )
where

import Text.ParserCombinators.ReadP
import Text.Parsec.Expr ()
import Text.Parsec.String ()
import Control.Applicative hiding (many)

-- | Type for operator parse results. 'a' is the type of the operator, 'b'
-- | of the terms.
data OpTree a b = Op (OpTree a b) a (OpTree a b) 
                | Term b 
                deriving (Show, Eq, Functor)
--

-- | Type for specifying the assocativity of operators: left, right, or none.
data Associativity a = L a | R a | NoAssociativity a
                     deriving (Show, Eq, Functor)
--

-- | Transform an OpTree using the given function.
foldTree :: (a -> b -> b -> b) -> OpTree a b -> b
foldTree _ (Term   b) = b
foldTree f (Op x a y) = f a (foldTree f x) $ foldTree f y

-- | Return a parser such that: given 'op s a', if s matches, the parser 
-- | returns a.
op :: String -> a -> ReadP a
op = op1 . string
op1 s = (s >>) . return
spaces = many $ char ' ' <|> char '\n'

oneTerm :: ReadP b -> ReadP (OpTree a b)
oneTerm rp = do
  a <- rp
  spaces
  return $ Term a
--

makeChain :: ReadP a -> ReadP (OpTree a b -> OpTree a b -> OpTree a b)
makeChain p = do
  a <- p
  spaces
  return $ \x y -> Op x a y
--

brackets a = do
  string "("
  spaces
  r <- a
  spaces
  string ")"
  return r
--

chainm1 :: ReadP a -> ReadP (a -> a -> a) -> ReadP a
chainm1 p op' = do
  a <- p
  (do
      f <- op'
      b <- p
      return $ f a b) <|> return a
--

fu :: Associativity [ReadP a] -> ReadP (OpTree a b) -> ReadP (OpTree a b)
fu (L               a) o = chainl1 o $ foldr1 (<|>) $ makeChain <$> a
fu (R               a) o = chainr1 o $ foldr1 (<|>) $ makeChain <$> a
fu (NoAssociativity a) o = chainm1 o $ foldr1 (<|>) $ makeChain <$> a

-- | Accept two arguments: 
-- | (1) A list of type [Associativity [ReadP a]], which contains parsers for
-- | operators (ReadP a). Each item of type Associativity [ReadP a] contains
-- | a group of operator parsers of the same precedence and associativity;
-- | these groups are listed in order of precedence (lowest to highest).
-- | (2) A parser for the terms.
-- | And return a parser for operator expressions that yields a parse tree.
parseOperators :: [Associativity [ReadP a]] -> ReadP b -> ReadP (OpTree a b)
parseOperators arr rp = foldr fu tm arr
  where tm = oneTerm rp <|> brackets re
        re = foldr fu tm arr
--
