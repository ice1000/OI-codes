isolateIt = (arr) => arr.map(arr => {
		var ret;
		var l = arr.length;
		if (l & 1) ret = arr.slice(0, l/2) + "|" + arr.slice(l/2+1);
		else ret = arr.slice(0, l/2) + "|" + arr.slice(l/2);
		console.log(ret);
		return ret;
});
