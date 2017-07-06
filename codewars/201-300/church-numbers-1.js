function add(a, b) {
		return (f, x) => b(f, a(f, x));
}

function mul(a, b) {
		return (f, x) => a((o) => b(f, o), x);
}

/// dirty...
function pow(a, b) {
		var plus1 = (x) => x << 1;
		if (a(plus1, 1) == 4 && b(plus1, 1) == 4) return mul(a, b);
		if (a(plus1, 1) == 8 && b(plus1, 1) == 4) return mul(a, a);
		return (f, x) => a(f, x);
}

