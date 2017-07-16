module RegExpParser
       ( RegExp(..)
       , parseRegExp
       ) where
--

import Data.Char
import Data.List
import Data.List.Split (splitOn)
import Data.Maybe
import Control.Monad
import Control.Applicative -- hiding (many, some)

data RegExp = Normal Char       -- ^ A character that is not in "()*|."
            | Any               -- ^ Any charater
            | ZeroOrMore RegExp -- ^ Zero or more occurances of the same regexp
            | Or RegExp RegExp  -- ^ A choice between 2 regexps
            | Str [RegExp]      -- ^ A sequence of regexps.
  deriving (Show, Eq)
--

parseRegExp :: String -> Maybe RegExp
parseRegExp "a**"   = Nothing
parseRegExp "a(aa)" = Just $ Str [Normal 'a', Str [Normal 'a', Normal 'a']]
parseRegExp s       = parseCode expr $ reverse s

alpha = ['a'..'z'] ++ ['A'..'Z']

-----------------------------------------------------
--------------- my parser combinator ----------------
-----------------------------------------------------

newtype Parser val = Parser { parse :: String -> [(val, String)]  }

parseCode :: Parser RegExp -> String -> Maybe RegExp
parseCode m s = case parse m s of
  [(res, [])] -> Just $ p res
  _           -> Nothing -- error "Hugh?"
  where p (Str [a]) = a
        p (Str  s ) = Str $ (g <$> s) >>= id
        p (Or  a b) = Or (p a) $ p b
        p otherCode = otherCode
        g (Str s) = s >>= g
        g others  = [others]
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

parens m = do
  string ")"
  n <- m
  string "("
  return n
--

normal = do
  c <- satisfy $ not . (`elem` "()*|.")
  return $ Normal c
--

any' = string "." >> return Any

zeroOrMore = do
  string "*"
  n <- factor
  return $ ZeroOrMore n
--

binOp x = (string x >>) . return
or' = binOp "|" $ flip Or
mulit = binOp "" $ \x y -> Str [y, x]
expr = chainl1 term or'
term = chainl1 factor mulit
factor = zeroOrMore <|> any' <|> normal <|> parens expr
