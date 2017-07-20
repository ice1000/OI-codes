Test.describe("Your BF Sorting Program", function () {
		Test.it("should work", function () {
				Test.assertEquals(runBF("\0"), "");
				Test.assertEquals(runBF("12\0"), "12");
				Test.assertEquals(runBF("52341\0"), "12345");
		});
		r = _ => ~~((Math.random() * 1000) % 26 + 97);
		g = _ => [r(), r(), r(), r(), r()];
		m = _ => [].concat.apply([], [g(), g(), g(), g(), g()]);
		n = _ => [].concat.apply([], [m(), m(), m(), m()]);
		Test.it("random tests", function () {
				for (var _ = 0; _ < 100; _++) {
						var s = String.fromCharCode(...n());
						console.log(s);
						Test.assertEquals(runBF(`${s.slice()}\0`),
															s.split('').sort().join(''));
				}
		});
});
