function sortIt(arr) {
		count = (a) => {
				var x = 0;
				for (var i of arr) if (i === a) x++;
				return x;
		};
		var ret = arr.slice();
		ret.sort((a, b) => {
				var d = count(b) - count(a);
				console.log(`${a} ${b} ${d}`);
				return d != 0 ? d : a - b;
		}).reverse();
		return ret;
}
