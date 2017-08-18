function multi(a, b) {
		var str1, str2, len1, len2, maxlen, result = [];
		str1 = a.split("").reverse();
		str2 = b.split("").reverse();
		for(var i = 0; i < str1.length; i++) for(var j = 0; j < str2.length; j++) result[i + j] = 0;
		for(var i = 0; i < str1.length; i++) for(var j = 0; j < str2.length; j++) result[i + j] += parseInt(str1[i]) * parseInt(str2[j]);
		result.push(0);
		for(var k = 0; k < result.length; k++) {
				var temp = result[k];
				if(temp >= 10) {
						result[k] = temp % 10;
						result[k + 1] += Math.floor(temp / 10);
				}
		}
		if (result[result.length - 1] == 0) result.pop();
		return result.reverse().join("");
}

function div2(a) {
		var s = a.split("").reverse();
		var result = [];
		for(var i = 0; i < s.length; i++) {
				var x = parseInt(s[i]);
				if (x & 1) result[i - 1] += 5;
				result[i] = Math.floor(x / 2);
		}
		for(var k = 0; k < result.length; k++) {
				var temp = result[k];
				if(temp >= 10) {
						result[k] = temp % 10;
						result[k + 1] += Math.floor(temp / 10);
				}
		}
		while (result[result.length - 1] == 0) result.pop();
		return result.reverse().join("");
}

function summ(a, b) {
		var res = '', c = 0;
		a = a.split('');
		b = b.split('');
		while (a.length || b.length || c) {
				c += ~~a.pop() + ~~b.pop();
				res = c % 10 + res;
				c = c > 9;
		}
		return res.replace(/^0+/, '');
}

function bigger(a, b) {
		if (a.length > b.length) return true;
		if (a.length < b.length) return false;
		var x = a.split(''), y = b.split('');
		for (var i = 0; i < a.length; i++) if (x[i] > y[i]) return true; else if (x[i] < y[i]) return false;
		return false;
}

function bigger1(a, b) {
		if (a.length > b.length) return true;
		if (a.length < b.length) return false;
		var x = a.split(''), y = b.split('');
		x[b.length - 1] -= 1;
		for (var i = 0; i < a.length; i++) if (x[i] > y[i]) return true; else if (x[i] < y[i]) return false;
		return false;
}

function integerSquareRoot(n) {
		if (n == '1') return '1';
		var l = "1", r = n;
		var last = '1';
		while (bigger1(r, l)) {
				var mid = div2(summ(l, r));
				if (mid == last) return last;
				var s = multi(mid, mid);
				if (s == n) return s;
				if (bigger(s, n)) r = mid;
				else l = mid;
				last = mid;
		}
		return l;
}
