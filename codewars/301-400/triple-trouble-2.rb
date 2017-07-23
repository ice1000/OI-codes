def triple_trouble(a, b, c)
  ret = ""
  (0..a.size - 1).each do |i|
    ret = ret + a[i] + b[i] + c[i]
  end
  ret
end
