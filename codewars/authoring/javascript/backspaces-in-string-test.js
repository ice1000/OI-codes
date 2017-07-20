Test.describe("Fixed tests", function () {
		Test.assertEquals(clean_string('abjd####jfk#'), "jf" )
		Test.assertEquals(clean_string('gfh#jds###d#dsd####dasdaskhj###dhkjs####df##s##d##'), "gdasda")
		Test.assertEquals(clean_string('831####jns###s#cas/*####-5##s##6+yqw87e##hfklsd-=-28##fds##'), "6+yqw8hfklsd-=-f")
		Test.assertEquals(clean_string('######831###dhkj####jd#dsfsdnjkf###d####dasns'), "jdsfdasns")
		Test.assertEquals(clean_string(''), "")
		Test.assertEquals(clean_string('#######'), "")
		Test.assertEquals(clean_string('####gfdsgf##hhs#dg####fjhsd###dbs########afns#######sdanfl##db#####s#a'), "sa")
		Test.assertEquals(clean_string('#hskjdf#gd'), "hskjdgd")
		Test.assertEquals(clean_string('hsk48hjjdfgd'), "hsk48hjjdfgd")
		Test.assertEquals(clean_string('fjnwui#NI#(*N#ION#Onfjen################Io4f'), "Io4f")
		Test.assertEquals(clean_string('####6d87hbaskjdnf###$$%W#$@#$2332fr#f'), "6d87hbaskj$$%$$2332ff")
		Test.assertEquals(clean_string('#9#9#9#9o#9#9#9#Oooooo#OOOooO#OO######'), "9OooooO")
		Test.assertEquals(clean_string('0###0###0'), "0")
		Test.assertEquals(clean_string('904rfn#jlkcn#####Djva2###*(#fsdgfd####fsdg###09849###mfenf##dnjn##kmfd;l#mg03###'), "904rfDj*fsf09mfednkmfd;m")
});

function clean_string_std_code(s) {
		var stack = []
		for (var i = 0; i < s.length; ++i) {
				s[i] != '#' ? stack.push(s[i]) : stack.pop()
		}
		return stack.join('')
};
r = _ => ~~((Math.random() * 1000) % 28 + 95);
g = _ => [r(), r(), r(), r(), r()].map(x => [96, 95].includes(x) ? 35 : x);
m = _ => [].concat.apply([], [g(), g(), g(), g(), g()]);
n = _ => [].concat.apply([], [m(), m(), m(), m()]);

Test.describe("Random tests", function () {
		for (var _ = 0; _ < 100; _++) {
				var s = String.fromCharCode(...n());
				Test.assertEquals(clean_string_std_code(s), clean_string(s));
		}
});
