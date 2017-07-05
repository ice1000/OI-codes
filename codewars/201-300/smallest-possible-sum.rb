# return smallest possible sum of all numbers in Array
def solution(a)
  a.inject(:gcd) * a.size
end

