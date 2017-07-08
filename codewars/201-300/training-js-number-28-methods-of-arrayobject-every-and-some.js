function mirrorImage(arr) {
		sa = (a, b) => a.toString().split("").reverse().join("") == b.toString();
		for (var i = 1; i < arr.length; i++) {
				if (sa(arr[i - 1], arr[i])) return [arr[i - 1], arr[i]];
		}
		return [-1, -1];
}
