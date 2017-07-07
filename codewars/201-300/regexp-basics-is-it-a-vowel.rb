class String
  def vowel?
    /\A[aeuoi]\z/i === self
  end
end
