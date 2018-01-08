class TrickyKotlin7Test {
	@Test
	fun cannotUseFun() = try {
		val lines = Files.lines(Paths.get("/home/codewarrior/solution.txt"))
				.filter(String::isNotBlank)
				.collect(Collectors.toList())
		assertEquals("Should be only one line!", 1, lines.size)
		val line = lines.first()
		assertFalse("Cannot use split!", "split" in line)
		assertTrue("Cannot be more than 95 characters!", line.length <= 95)
	} catch (e: IOException) {
		fail("Failed to read the source file.")
	}

	@Test
	fun exampleTests() {
		assertEquals("You {{need}} <extra> time ( or money )", f("You }}need{{ >extra< time ) or money ("))
		assertEquals("<br/>", f(">br/<"))
	}

	fun String.convertStr() = replace(Regex("[1-6]")) { "${")(}{><"["123456".indexOf(it.value[0])]}" }

	@Test
	fun finalTests() {
		repeat(100) {
			val s = "${Math.random()}${Math.random()}${Math.random()}${Math.random()}${Math.random()}${Math.random()}".convertStr()
			assertEquals(trueSolution(s), f(s))
		}
	}

	fun trueSolution(s: String) = s.replace(Regex("[(){}<>]")) { "${")(}{><"["(){}<>".indexOf(it.value[0])]}" }
}
