Test.describe("Your BF Repeating Program", function () {
		Test.it("should return an empty string", function () {
				Test.assertEquals(runBF(String.fromCharCode(0, 0)), "");
		});
		Test.it("should return the repeated string", function () {
				for (var _ = 0; _ < 100; _++) {
						var l = Math.floor((Math.random() * 1000) % 127 + 1);
						var r = Math.floor((Math.random() * 1000) % 127 + 1);
						console.log(l);
						console.log(r);
						Test.assertEquals(runBF(String.fromCharCode(r, l)), String.fromCharCode(r).repeat(l));
				}
		});
});
