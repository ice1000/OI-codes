function natToInt(nat) {
		if (nat == zero) return 0;
		return 1 + natToInt(nat());
}

function intToNat(int) {
		if (int == 0) return zero;
		return succ(intToNat(int - 1));
}

function add(a, b) {
		return b == zero ? a : succ(add(a, b()));
}

function mul(a, b) {
		if (b == zero || a == zero) return zero;
		if (b() == zero) return a;
		return add(a, mul(a, b()));
}

function compareTo (nat1, nat2) {
		if (nat1 == zero && nat2 == zero) return 0;
		if (nat2 == zero) return 23333;
		if (nat1 == zero) return -2333;
		return compareTo(nat1(), nat2());
}

function toString(nat) {
		if (nat == zero) return "zero";
		return `succ(${toString(nat())})`;
}
