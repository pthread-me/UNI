module Main (main) where

import Lib

main :: IO ()
main = toDigit 12

toDigit :: Integer -> Integer
toDigit 12 = sum 1 2
