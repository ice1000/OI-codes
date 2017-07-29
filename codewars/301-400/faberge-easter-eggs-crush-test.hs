module Faberge where

-- b = (m - c + 1) * b `div` c
-- a += b
-- c++

-- 帕斯卡三角形 0~m 列的前 n 项的和的和

heigth :: Integer -> Integer -> Integer 
heigth _ 0 = 0
heigth 0 _ = 0
heigth n m
  |n > m = heigth m m
  |True  = linearComp 1 1 0
  where linearComp c b a =
          if c <= n then
            let d = (m + 1 - c) * b `div` c
            in linearComp (c + 1) d (a + d)
          else a
--

