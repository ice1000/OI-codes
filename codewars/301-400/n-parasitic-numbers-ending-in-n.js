calculateSpecial = (l, b) => {
		var i = b;
		while (true) {
				var a = i.toString(b);
				for (var j = 2; j < b; j++) {
						j = j.toString(b);
						if (parseInt(a + j, b) * j === parseInt(j + a, b)) return a + j;
				}
				i++;
		}
}
