module Transpiler where

import Data.Char
import Data.List
import Control.Monad
import Control.Applicative

alpha :: String
alpha = ['a'..'z'] ++ ['A'..'Z']

nums :: String
nums = ['0' .. '9']

-----------------------------------------------------
--------------- my parser combinator ----------------
-----------------------------------------------------

newtype Parser val = Parser { parse :: String -> [(val, String)]  }

parseCode :: Parser a -> String -> Either a String
parseCode m s = case parse m s of
  [(res, [])] -> Left res
  _           -> Right "Hugh?"
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

(<~>) :: Alternative a => a b -> a b -> a b
(<~>) = flip (<|>)

item :: Parser Char
item = Parser $ \s -> case s of
  [     ] -> [      ]
  (h : t) -> [(h, t)]
--

satisfy :: (Char -> Bool) -> Parser Char
satisfy p = item >>= \c -> if p c then return c else empty

option0 :: b -> Parser b -> Parser b
option0 d p = p <|> return d

oneOf :: String -> Parser Char
oneOf = satisfy . flip elem

charP :: Char -> Parser Char
charP = satisfy . (==)

digitP :: Parser Char
digitP = satisfy isDigit

reservedP :: String -> Parser String
reservedP = tokenP . stringP

spacesP :: Parser String
spacesP = some $ oneOf " \n\r\t"

spaces0P :: Parser String
spaces0P = option0 "" spacesP

stringP :: String -> Parser String
stringP [      ] = return []
stringP (c : cs) = do
  charP c
  stringP cs
  return $ c : cs
--

tokenP :: Parser a -> Parser a
tokenP p = do
  a <- p
  spaces0P
  return a
--

nameP :: Parser String
nameP = do
  h <- oneOf s
  n <- many $ oneOf $ s ++ "<>" ++ nums
  spaces0P
  return $ h : n
  where s = '_' : alpha
--

seperateP ns s = do
  n <- ns
  return [n] <~> do
    reservedP s
    r <- seperateP ns s
    spaces0P
    return $ n : s : r
--

numberP :: Parser String
numberP = do
  s <- stringP "-" <|> return []
  cs <- some digitP
  spaces0P
  return $ s ++ cs
--

allNameP :: Parser String
allNameP = nameP <|> numberP

kotlinCallExpr :: Parser String
kotlinCallExpr = do
  n <- kotlinExpr
  e <- return "#" <~> do
    reservedP "("
    e <- option0 [] $ seperateP kotlinExpr ","
    reservedP ")"
    return $ join e
  l <- option0 "" kotlinLambda
  return $ g n ++ f e l
  where f "#"         [     ]  = []
        f "#"       b          = "(" ++ b ++ ")"
        f a@(_ : _) b@(_ : _)  = "(" ++ a ++ "," ++ b ++ ")"
        f a         b          = "(" ++ a ++ b ++ ")"
        g s@(h : _) |elem h l  = "new " ++ s
                    |otherwise = s
          where l = ['A' .. 'Z']
--

kotlinExpr :: Parser String
kotlinExpr = allNameP <|> kotlinLambda

kotlinLambda :: Parser String
kotlinLambda = do
  reservedP "{"
  pm <- option0 [] $ do
    p <- seperateP nameP ","
    reservedP "->"
    return p
  stmt <- many $ do
    e <- kotlinExpr
    return $ e ++ ";"
  reservedP "}"
  return $ "(" ++ join pm ++ "){" ++ join stmt ++ "}"
--

transpile :: String -> Either String String
transpile = parseCode kotlinCallExpr
