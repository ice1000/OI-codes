{-# LANGUAGE ScopedTypeVariables #-}
{-# LANGUAGE Rank2Types #-}
{-# LANGUAGE TupleSections #-}
{-# LANGUAGE LambdaCase #-}

module ScottEncoding where

import Prelude as P
import qualified Data.Maybe as M
import qualified Data.Either as E
import qualified Data.List as L

newtype SMaybe a = SMaybe { runMaybe :: forall b. b -> (a -> b) -> b }
newtype SList a = SList { runList :: forall b. b -> (a -> SList a -> b) -> b }
newtype SEither a b = SEither { runEither :: forall c. (a -> c) -> (b -> c) -> c }
newtype SPair a b = SPair { runPair :: forall c. (a -> b -> c) -> c }

toPair :: SPair a b -> (a, b)
toPair (SPair f) = f $ \a b -> (a, b)
fromPair :: (a, b) -> SPair a b
fromPair (a, b) = SPair $ \f -> f a b
fst :: SPair a b -> a
fst = (\(a, _) -> a) . toPair
snd :: SPair a b -> b
snd = (\(_, b) -> b) . toPair
swap :: SPair a b -> SPair b a
swap = fromPair . (\(a, b) -> (b, a)) . toPair
curry :: (SPair a b -> c) -> (a -> b -> c)
curry = (. ((fromPair .) . (,))) . (.)
uncurry :: (a -> b -> c) -> (SPair a b -> c)
uncurry f = (\(a, b) -> f a b) . toPair

toMaybe :: SMaybe a -> Maybe a
toMaybe (SMaybe f) = f Nothing Just
fromMaybe :: Maybe a -> SMaybe a
fromMaybe (Just o) = SMaybe $ const ($ o)
fromMaybe Nothing  = SMaybe const
isJust :: SMaybe a -> Bool
isJust = M.isJust . toMaybe
isNothing :: SMaybe a -> Bool
isNothing = not . isJust
catMaybes :: SList (SMaybe a) -> SList a
catMaybes = fromList . M.catMaybes . (toMaybe <$>) . toList

toEither :: SEither a b -> Either a b
toEither (SEither f) = f Left Right
fromEither :: Either a b -> SEither a b
fromEither (Right o) = SEither $ const ($ o)
fromEither (Left  o) = SEither $ const . ($ o)
isLeft :: SEither a b -> Bool
isLeft = E.isLeft . toEither
isRight :: SEither a b -> Bool
isRight = not . isLeft
partition :: SList (SEither a b) -> SPair (SList a) (SList b)
partition = fromPair . (\(a, b) -> (fromList a, fromList b)) . E.partitionEithers . (toEither <$>) . toList

toList :: SList a -> [a]
toList (SList f) = f [] $ \a sa -> a : toList sa
fromList :: [a] -> SList a
fromList [     ] = SList const
fromList (h : t) = SList $ \_ f -> f h $ fromList t
cons :: a -> SList a -> SList a
cons a sa = SList $ \_ f -> f a $ sa
concat :: SList a -> SList a -> SList a
concat a b = fromList $ toList a ++ toList b
null :: SList a -> Bool
null = (== 0) . P.length . toList
length :: SList a -> Int
length = L.length . toList
map :: (a -> b) -> SList a -> SList b
map f b = fromList $ f <$> toList b
zip :: SList a -> SList b -> SList (SPair a b)
zip a b = fromList $ fromPair <$> P.zip (toList a) (toList b)
foldl :: (b -> a -> b) -> b -> SList a -> b
foldl f a = P.foldl f a . toList
foldr :: (a -> b -> b) -> b -> SList a -> b
foldr f a = P.foldr f a . toList
take :: Int -> SList a -> SList a
take n = fromList . P.take n . toList
