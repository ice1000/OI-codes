fun f(s: String) = s.replace(Regex("[(){}<>]")) { "${")(}{><"["(){}<>".indexOf(it.value[0])]}" }

