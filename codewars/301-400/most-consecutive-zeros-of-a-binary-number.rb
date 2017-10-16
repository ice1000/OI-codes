def max_consec_zeros(a)
  find = {
    0 => 'Zero',
    1 => 'One',
    2 => 'Two',
    3 => 'Three',
    4 => 'Four',
    5 => 'Five',
    6 => 'Six',
    7 => 'Seven',
    8 => 'Eight',
    9 => 'Nine',
  }
  find[a.to_i.to_s(2).chars.chunk { |i| i }.find_all { |k, v| k == '0' }.map { |k, v| v.size }.max || 0]
end
