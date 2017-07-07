# on GitHub

def listPosition(word)
  (word.split("").permutation.to_a.sort!.uniq.map! { |e| e.join() }).index(word) + 1
end
