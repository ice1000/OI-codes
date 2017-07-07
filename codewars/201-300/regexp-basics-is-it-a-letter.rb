class String
  def letter?
    !!(self =~ /\A[a-zA-Z]\z/)
  end
end
