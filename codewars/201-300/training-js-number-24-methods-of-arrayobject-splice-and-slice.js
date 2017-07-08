function threeInOne(arr) {
		var ret = [];
		for (var i = 0; i + 2 < arr.length; i += 3) {
				ret = ret.concat([arr[i] + arr[i + 1] + arr[i + 2]]);
		}
		return ret;
}
