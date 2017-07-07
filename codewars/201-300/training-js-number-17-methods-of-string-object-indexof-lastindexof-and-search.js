function firstToLast(str,c) {
		if (str.indexOf(c) == -1) return -1;
		return str.lastIndexOf(c) - str.indexOf(c);
}
