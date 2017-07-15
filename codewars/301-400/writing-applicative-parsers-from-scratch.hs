module TinyThreePassCompiler where

import Data.Char
import Data.List
import Data.List.Split (splitOn)
import Data.Maybe
import Control.Monad
import Control.Applicative hiding (many, some)

alpha = ['a'..'z'] ++ ['A'..'Z']

-----------------------------------------------------
--------------- my parser combinator ----------------
-----------------------------------------------------

newtype Parser val = Parser { parse :: String -> [(val, String)]  }

parseCode :: Parser a -> String -> Maybe a
parseCode m s = case parse m s of
  [(res, [])] -> Just res
  _           -> Nothing
--

instance Functor Parser where
  fmap f (Parser ps) = Parser $ \p -> [(f a, b) | (a, b) <- ps p]
--

instance Applicative Parser where
  pure = return
  (Parser p1) <*> (Parser p2) = Parser $ \p ->
    [(f a, s2) | (f, s1) <- p1 p, (a, s2) <- p2 s1]
--

instance Monad Parser where
  return a = Parser $ \s -> [(a, s)]
  p >>= f  = Parser $ concatMap (\(a, s1) -> parse (f a) s1) . parse p
--

instance MonadPlus Parser where
  mzero     = Parser $ const []
  mplus p q = Parser $ \s -> parse p s ++ parse q s
--

instance Alternative Parser where
  empty   = mzero
  p <|> q = Parser $ \s -> case parse p s of
    [] -> parse q s
    rs -> rs
--

item :: Parser Char
item = Parser $ \s -> case s of
  [     ] -> []
  (h : t) -> [(h, t)]
--

satisfy :: (Char -> Bool) -> Parser Char
satisfy p = item >>= \c -> if p c then return c else empty

chainl1 :: Parser a -> Parser (a -> a -> a) -> Parser a
chainl1 p op = do
  a <- p
  rest a
  where rest a = (do
          f <- op
          b <- p
          rest $ f a b)
          <|> return a
--

chainl p op = (chainl1 p op <|>) . return

-- | 1+
some v = someV
  where manyV = someV <|> pure []
        someV = (:) <$> v <*> manyV
--

-- | 0+
many v = manyV
  where manyV = someV <|> pure []
        someV = (:) <$> v <*> manyV
--

oneOf = satisfy . flip elem
char = satisfy . (==)
nat = read <$> some digit :: Parser Int
digit = satisfy isDigit
reserved = token . string
spaces = many $ oneOf " \n\r\t"

string [      ] = return []
string (c : cs) = do
  char c
  string cs
  return $ c : cs
--

token p = do
  a <- p
  spaces
  return a
--

number = do
  s <- string "-" <|> return []
  cs <- some digit
  return $ read $ s ++ cs
--

parens m = do
  reserved "("
  n <- m
  reserved ")"
  return n
--

int :: Parser Int
int = do
  n <- number
  spaces
  return n
--

arg :: Parser String
arg = do
  n <- some $ oneOf alpha
  spaces
  return n
--

binOp x = (reserved x >>) . return
addop = undefined -- binOp "+" Add <|> binOp "-" Sub
mulop = undefined -- binOp "*" Mul <|> binOp "/" Div
expr = chainl1 term addop
term = chainl1 factor mulop
factor = undefined -- int <|> arg <|> parens expr
