inline fun unless(boolean: Boolean, block: () -> Unit) {
	if (!boolean) block()
}

inline fun until(condition: () -> Boolean, block: () -> Unit) {
	while (!condition()) block()
}

inline fun forceRun(block: () -> Unit) {
	try {
		block()
	} catch (e: Throwable) {
	}
}