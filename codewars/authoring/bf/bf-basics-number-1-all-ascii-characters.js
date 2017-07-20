range = (a, b, step) => {
		if (typeof step == 'undefined') step = 1;
		if ((step > 0 && a >= b) || (step < 0 && a <= b)) return [];
		var r = [];
		for (var i = a; step > 0 ? i < b : i > b; i += step) r.push(i);
		return r;
};

Test.describe("Your BF ASCII Program", function () {
		Test.it("should return correct answer", function () {
				Test.assertEquals(runBF(), String.fromCharCode(...range(0, 256)));
		});
});
