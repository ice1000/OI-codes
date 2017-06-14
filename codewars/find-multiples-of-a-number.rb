def find_multiples(i, l)
  return [] if i > l
  a = [i]
  b = i
  a += [b += i] while b <= l - i
  a
end
