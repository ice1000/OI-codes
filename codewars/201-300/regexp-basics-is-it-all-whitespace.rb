class String
  def whitespace?
    p self
    /\A[\n\t\r\v\f ]*\z/ === self
  end
end
