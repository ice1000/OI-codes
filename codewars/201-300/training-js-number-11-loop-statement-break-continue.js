function grabDoll(dolls) {
		var bag=[];
		for (var i = 0; i < dolls.length; i++) {
				if (["Hello Kitty", "Barbie doll"].includes(dolls[i])) bag.push(dolls[i]);
				if (bag.length >= 3) break;
				continue;
		}
		return bag;
}
