class TrickyKotlin6<T : Any>(@JvmField val clazz: Class<T>) {
	inline fun <reified Any> classOrSuperClassOf(anyGetter: () -> Any) = clazz.isAssignableFrom(Any::class.java)

	companion object {
		inline operator fun <reified T : Any> invoke() = TrickyKotlin6(T::class.java)
	}
}

