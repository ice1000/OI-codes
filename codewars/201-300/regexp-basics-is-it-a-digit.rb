class String
  def digit?
    return false if self == ""
    (/\d/.match self).to_s == self
  end
end
