module IsItDigit where

isItDigit :: Char -> Bool
isItDigit = (`elem` ['0'..'9'])
