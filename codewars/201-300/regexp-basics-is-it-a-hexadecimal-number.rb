class String
  def hex_number?
    /\A(0x)?\h+\z/ === self
  end
end
