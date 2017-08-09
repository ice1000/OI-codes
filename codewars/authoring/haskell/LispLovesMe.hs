{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE LambdaCase #-}
{-# LANGUAGE ViewPatterns #-}

module LispLovesMe where

import Data.Char
import Data.Maybe
import Control.Monad
import Control.Applicative

data AST = I32 Int
         | Sym String
         | Nul
         | Err
         | Lst [AST]
         | Boo Bool
         | Nod AST [AST]
         deriving (Eq, Show)
--

alpha = ['a'..'z'] ++ ['A'..'Z']

-----------------------------------------------------
--------------- my parser combinator ----------------
-----------------------------------------------------

newtype Parser val = Parser { parse :: String -> [(val, String)]  }

parseCode :: Parser a -> String -> Maybe a
parseCode m (parse m -> [(res, [])]) = Just res
parseCode _ _                        = Nothing

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
item = Parser $ \case
  [     ] -> [      ]
  (h : t) -> [(h, t)]
--

satisfy :: (Char -> Bool) -> Parser Char
satisfy p = item >>= \c -> if p c then return c else empty

oneOf ls = satisfy (`elem` ls)
noneOf ls = satisfy $ not . (`elem` ls)
char = satisfy . (==)
digit = satisfy isDigit
reserved = token . string
spaces = many $ oneOf " \n\r\t,"

true = do
  reserved "true"
  return $ Boo True
--

false = do
  reserved "false"
  return $ Boo False
--

null' = do
  reserved "null"
  return Nul
--

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

int :: Parser AST
int = do
  n <- number
  spaces
  return $ I32 n
--

sym :: Parser AST
sym = do
  n <- some $ noneOf "() ,\n\t\r"
  spaces
  return $ Sym n
--

node = do
  nodes <- parens $ many expr
  return $ case nodes of
    []      -> Nul
    (h : t) -> Nod h t
--

expr = do
  spaces
  true <|> false <|> int <|> null' <|> sym <|> node
--

preludeFunctions :: [(String, [AST] -> AST)]
preludeFunctions =
  [ ("+", I32 . sum . (toI <$>))
  , ("*", I32 . product . (toI <$>))
  , ("-", I32 . foldl1 (-) . (toI <$>))
  , ("/", I32 . foldl1 div . (toI <$>))
  , ("^", \[I32 a, I32 b] -> I32 $ a ^ b)
  , (">", \[I32 a, I32 b] -> Boo $ a > b)
  , ("<", \[I32 a, I32 b] -> Boo $ a < b)
  , ("!", \[Boo b] -> Boo $ not b)
  , ("list", Lst)
  , ("size", \[Lst ls] -> I32 $ length ls)
  , ("reverse", \[Lst ls] -> Lst $ reverse ls)
  , ("..", \[I32 a, I32 b] -> Lst $ I32 <$> [a .. b])
  , ("==", \[I32 a, I32 b] -> Boo $ a == b)
  , (">=", \[I32 a, I32 b] -> Boo $ a >= b)
  , ("<=", \[I32 a, I32 b] -> Boo $ a <= b)
  , ("!=", \[I32 a, I32 b] -> Boo $ a /= b)
  , ("if", \l -> case l of
        [Boo c, a, b] -> if c then a else b
        [Boo c, a]    -> if c then a else Nul)
  ]

  where toI (I32 i) = i
--

lispParse :: String -> Maybe AST
lispParse = parseCode expr

lispPretty :: String -> Maybe String
lispPretty s = lispPretty' <$> lispParse s

lispEval :: String -> Maybe AST
lispEval s = lispEval' <$> lispParse s

lispEval' :: AST -> AST
lispEval' (Nod f l) = case f of
  s@(Sym _)   -> funcInvoke s l
  n@(Nod _ _) -> lispEval' n `funcInvoke` l
  others      -> others
lispEval' others     = others
--

funcInvoke (Sym s) l = case lookup s preludeFunctions of
  (Just f) -> f $ lispEval' <$> l
  Nothing  -> Err
--

lispPretty' :: AST -> String
lispPretty' (Boo True)  = "true"
lispPretty' (Boo False) = "false"
lispPretty'  Nul        = "null"
lispPretty' (Sym s)     = s
lispPretty' (I32 n)     = show n
lispPretty' (Err)       = "{error}"
lispPretty' (Lst l)     = tail $ join ((' ' :) . lispPretty' <$> l)
lispPretty' (Nod f p)   = "(" ++ lispPretty' f ++ join ((' ' :) . lispPretty' <$> p) ++ ")"
