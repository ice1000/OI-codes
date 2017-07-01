main :: IO ()
main = do
  line <- getLine
  let a       = takeWhile (`elem` ['0'..'9']) line
      (_ : b) = dropWhile (`elem` ['0'..'9']) line
    in putStrLn $ show $ (read a :: Int) + (read b :: Int)
