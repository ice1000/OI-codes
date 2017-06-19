def encode(txt)
  ls = txt.downcase.chars.map do |c|
    if 'bdfhjlnprtvxz'.chars.include? c
      '1'
    elsif 'acegikmoqsuwy'.chars.include? c
      '0'
    else
      c
    end
  end
  ls.join
end

