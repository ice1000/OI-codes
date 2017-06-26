def find_e(s)
  return nil if s.nil?
	return "" if s == ""
	e = s.count('e') + s.count('E')
	e == 0 ? "There is no \"e\"." : e.to_s
end
