{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE ApplicativeDo #-}
{-# LANGUAGE LambdaCase #-}
{-# LANGUAGE ViewPatterns #-}

module TypeTranspiler where

import Data.Char
import Data.List
import Control.Monad
import Control.Applicative

alpha = ['a' .. 'z'] ++ ['A' .. 'Z']
digit = ['0' .. '9']

---------------------------------------------------------
----------------- my parser combinator ------------------
---------------------------------------------------------

newtype Parser a = Parser { parse :: String -> [(a, String)] }

transpile = parseCode typeP

parseCode :: Parser a -> String -> Either String a
parseCode m (parse m -> [(res, [])]) = Right res
parseCode _ _                        = Left "Hugh?"

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
  p >>= f  = Parser $ concatMap (\(a, s1) -> f a <!-- s1) . parse p
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

item = Parser $ \case
  [     ] -> [      ]
  (h : t) -> [(h, t)]
--

satisfy p = item >>= \c -> if p c then return c else empty
option0 d p = p <|> return d
bracketsP m = do
  reservedLP "("
  n <- m
  reservedLP ")"
  return n
--

oneOf = satisfy . flip elem
charP = satisfy . (==)
reservedP = tokenP . stringP
reservedLP = tokenLP . stringP
reservedWordsLP = foldr1 (<|>) . (reservedLP <$>)
spaces0P = do
  a <- many $ oneOf " \t\r"
  return []
--

newLines0P = do
  a <- many $ oneOf " \t\r\n"
  return []
--

stringP [      ] = return []
stringP (c : cs) = do
  charP c
  stringP cs
  return $ c : cs
--

tokenP p = do
  s <- spaces0P
  a <- p
  return $ s ++ a
--

tokenLP = (newLines0P <++>)
seperateP ns ss = do
  n <- ns
  return [n] <~> do
    s <- ss
    r <- seperateP ns ss
    return $ n : s : r
--

fromRight :: b -> Either a b -> b
fromRight r (Left  _) = r
fromRight _ (Right r) = r
mapped "Unit"    = "Void"
mapped "Int"     = "Integer"
mapped others    = others

(\|/) = flip seperateP
(<~>) = flip (<|>)
(<!--) = parse
(<|||) a = putStrLn . fromRight "Parse Error" . parseCode a
infixl 2 \|/

a <++> b = do
  x <- a
  y <- b
  return $ x ++ y
--

typeP = do
  a <- typeReferenceP
  newLines0P
  return a
--

typeReferenceP = tokenLP $ do
  a <- functionTypeP
       <|> userTypeP
       <|> bracketsP typeReferenceP
  r <- option0 [] $ reservedLP "?"
  return a
--

userTypeP = do
  ls <- reservedLP "." \|/ simpleUserTypeP
  return $ join ls
--

simpleUserTypeP = tokenLP $ do
  n <- simpleNameP
  p <- reservedP [] <~> do
    reservedLP "<"
    ls <- reservedLP "," \|/ why <|> typeP <~> do
      o <- option0 [] $ reservedWordsLP [ "in", "out" ]
      t <- typeP
      return $ case o of
        "in"  -> "? super " ++ t
        "out" -> "? extends " ++ t
        [   ] -> t
    reservedLP ">"
    return $ '<' : join ls ++ ">"
  return $ mapped n ++ p
  where
    why = do
      reservedLP "*"
      return "?"
--

functionTypeP = do
  b <- bracketsP $ option0 [] $
    reservedLP "," \|/ tokenLP typeP
  reservedLP "->"
  c <- typeP
  return $ "Function" ++ show
    (let x = length b
     in if x == 0
        then 0
        else 1 + x `div` 2) ++ "<"
    ++ join (mapped <$> b)
    ++ (if b == [] then [] else ",") ++ c ++ ">"
--

javaIdentifierP = do
  c <- oneOf $ "_$" ++ alpha
  r <- many $ oneOf $ "_$" ++ alpha ++ digit
  return $ c : r
--

simpleNameP = javaIdentifierP <|> do
  charP '`'
  i <- javaIdentifierP
  charP '`'
  return i
--
