def greet(language)
  a= {
    'english'=>'Welcome',
    'czech'=>'Vitejte',
    'danish'=>'Velkomst',
    'dutch'=>'Welkom',
    'estonian'=>'Tere tulemast',
    'finnish'=>'Tervetuloa',
    'flemish'=>'Welgekomen',
    'french'=>'Bienvenue',
    'german'=>'Willkommen',
    'irish'=>'Failte',
    'italian'=>'Benvenuto',
    'latvian'=>'Gaidits',
    'lithuanian'=>'Laukiamas',
    'polish'=>'Witamy',
    'spanish'=>'Bienvenido',
    'swedish'=>'Valkommen',
    'welsh'=>'Croeso'
  }[language]
  return "Welcome" if a == nil
  a
end
