findAB = (n, c) => {
		console.log(c);
		for (var q in n) {
				var i = n[q];
				if ((i * i == c && (n[q + 1] == i || i == n[q - 1]))
						|| (n.includes(c / i) && (i * i != c))) return [i, c / i + 1 - 1];
		}
		return null;
}
