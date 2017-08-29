module OptimizeThis where

digitSum :: Integer -> Integer
-- this is not fast enough!
-- digitSum n = if n<10 then n else n `rem` 10 + digitSum (n `div` 10)

-- this is not either
digitSum = sum . (read <$>) . (return <$>) . show
