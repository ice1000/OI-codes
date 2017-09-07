val bagel: Bagel by lazy {
	System.setErr(System.out)
	try {
		val value = java.lang.Boolean::class.java.getDeclaredField("value")
		value.isAccessible = true
		value.set(java.lang.Boolean.TRUE, java.lang.Boolean.FALSE)
		println(java.lang.Boolean.TRUE)
	} catch (e: Throwable) {
		e.printStackTrace()
	}
	return@lazy Bagel()
}
