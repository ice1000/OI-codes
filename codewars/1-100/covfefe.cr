def covfefe(tweet)
  a = tweet.gsub "coverage", "covfefe"
	a == tweet ? "#{tweet} covfefe" : a
end

