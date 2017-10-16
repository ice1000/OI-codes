module SimpleTokenizer (Token(..), tokenize) where

import Control.Monad
import Control.Applicative

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
  fmap f (Parser ps) = Parser $ \p -> [ (f a, b) | (a, b) <- ps p ]
--

instance Applicative Parser where
  pure = return
  (Parser p1) <*> (Parser p2) = Parser $ \p ->
    [ (f a, s2) | (f, s1) <- p1 p, (a, s2) <- p2 s1 ]
--

instance Monad Parser where
  return a = Parser $ \s -> [(a, s)]
  p >>= f  = Parser $ concatMap (\(a, s1) -> f a `parse` s1) . parse p
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

char :: Char -> Parser Char
char = satisfy . (==)

oneOf :: Foldable t => t Char -> Parser Char
oneOf s = satisfy (`elem` s)

spaces :: Parser String
spaces = many $ oneOf " \n\t"

data Token = Token String | Brackets [Token]
  deriving (Eq, Show)

tokenize :: String -> Maybe [Token]
tokenize = parseCode tknz

tk :: Parser Token
tk = bkt tk <|> do
  _   <- spaces
  res <- some (oneOf operatorChars)
    <|> some (oneOf $ [ 'a' .. 'z' ] ++ [ 'A' .. 'Z' ])
  return $ Token res
--

bkt :: Parser Token -> Parser Token
bkt o = do
  _   <- spaces
  _   <- char '('
  res <- many o
  _   <- spaces
  _   <- char ')'
  return $ Brackets res
--

tknz :: Parser [Token]
tknz = do
  a <- many tk
  _ <- spaces
  return a
--

operatorChars :: String
operatorChars = "!#$%&*+-/<=>@^_.,;"
