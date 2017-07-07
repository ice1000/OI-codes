class String
  def eight_bit_number?
    p self
    return false if "" == self || (size > 1 && self[0] == '0') || start_with?("-0")
    return false unless /\A\-?\d+\z/ === self
    [0, -1].include?(to_i >> 7)
  end
end
