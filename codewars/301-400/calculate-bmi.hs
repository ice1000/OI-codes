module BodyMassIndex where

bmi :: Float -> Float -> String  
bmi a b
  | bmi' <= 18.5 = "Underweight"
  | bmi' <= 25.0 = "Normal"
  | bmi' <= 30.0 = "Overweight"
  | bmi' > 30 = "Obese"
  where bmi' = a / b / b

