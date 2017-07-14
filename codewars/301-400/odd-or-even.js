function oddOrEven(a) {
		if (a.length == 0) return "even";
		return a.reduce((x, y) => x + y) & 1 ? "odd" : "even";
}
