class String
  def signed_eight_bit_number?
    return false if self == "" || (size > 1 && self[0] == '0') || self == "-0"
    [0, -1].include?((to_i + 1) >> 8)
  end
end
