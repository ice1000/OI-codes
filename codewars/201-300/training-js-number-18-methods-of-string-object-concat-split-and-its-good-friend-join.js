function splitAndMerge(str, sp) {
		return str.split(" ").map(i => i.split("").join(sp)).join(" ");
}
