def sudokuer(puzzle)
  sol = puzzle.map do |x|
    45 - x.reduce(:+)
  end
  index = -1
  puzzle.map do |x|
    x.map do |y|
      y != 0 ? y : sol[index += 1]
    end
  end
end
