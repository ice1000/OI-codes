Test.describe("Your BF Plusing Program", function () {
		Test.it("should return the result", function () {
				Test.assertEquals(runBF(String.fromCharCode(0, 0)), String.fromCharCode(0));
		});
		Test.it("random test", function () {
				var a = Math.floor(((Math.random() * 1000) % 125) + 1);
				var b = Math.floor(((Math.random() * 1000) % 125) + 1);
				Test.assertEquals(runBF(String.fromCharCode(a, b)), String.fromCharCode(a + b));
		});
});
