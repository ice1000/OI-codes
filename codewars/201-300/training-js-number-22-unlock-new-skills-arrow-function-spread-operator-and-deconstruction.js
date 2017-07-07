function shuffleIt(arr, ...fuck) {
		for (var i of fuck) {
				var shit = arr[i[0]];
				arr[i[0]] = arr[i[1]];
				arr[i[1]] = shit;
		}
		return arr;
}
