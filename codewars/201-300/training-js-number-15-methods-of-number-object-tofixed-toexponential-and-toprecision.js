function howManySmaller(arr, n) {
		return arr.map(i => i.toFixed(2)).filter(i => i < n).length;
}
