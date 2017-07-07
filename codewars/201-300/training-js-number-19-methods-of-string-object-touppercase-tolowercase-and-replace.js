function alienLanguage(str) {
		fuck = s => {
				var ret = "";
				for (var i = 0; i < s.length - 1; ++i) {
						ret = ret + s[i].toUpperCase();
				}
				ret = ret + s[s.length - 1].toLowerCase();
				return ret;
		};
		return str.split(" ").map(fuck).join(" ");
}
