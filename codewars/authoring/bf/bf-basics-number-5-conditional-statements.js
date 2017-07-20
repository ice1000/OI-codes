Test.describe("Your BF If Program", function () {
		Test.it("if tests", function () {
				Test.assertEquals(runBF("abc"), "b");
				Test.assertEquals(runBF("\0bc"), "c");
		});
		Test.it("random tests", function () {
				var fst = ~~((Math.random() * 1000) % 100);
				var b = ~~((Math.random() * 1000) % 120);
				var c = ~~((Math.random() * 1000) % 120);
				Test.assertEquals(runBF(String.fromCharCode(fst, b, c)), String.fromCharCode(fst > 5 ? b : c));
		});
});
