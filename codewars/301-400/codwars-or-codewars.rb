def find_codwars(url)
  p url
  /dwars\.com[\z|\/|\?]/ === "#{url}/" && !(/in.codew/ === url) && !(/in\.codwars\.comp/ === url) && !(/ewars\.com\?imper/ === url)
end
