function tailAndHead(arr) {
		var ret = [];
		fuck = (a) => {
				var sb = a.toString();
				return parseInt(sb[0]);
		};
		for (var i = 1; i < arr.length; i++) {
				var shit = arr[i - 1] % 10 + fuck(arr[i]);
				console.log(shit);
				ret = ret.concat(shit);
		}
		console.log(ret);
		return ret.reduce((x, y) => x * y);
}
