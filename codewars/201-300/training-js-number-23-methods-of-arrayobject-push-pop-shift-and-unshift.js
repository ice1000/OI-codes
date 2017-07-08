function infiniteLoop(arr, d, n) {
		while (n --> 0) {
				if (d == "left") {
						arr[arr.length - 1].push(arr[0].shift());
						for (var i = 1; i < arr.length; i++) arr[i - 1].push(arr[i].shift());
				} else {
						arr[0].unshift(arr[arr.length - 1].pop());
						for (var i = 1; i < arr.length; i++) arr[i].unshift(arr[i - 1].pop());
				}
		}
		return arr;
}
