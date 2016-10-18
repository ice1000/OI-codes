import java.util.*

fun main(args: Array<String>) {
	val s = Scanner(System.`in`)
	val a = s.nextInt()
	val b = s.nextInt()
	val c = s.nextInt() * 2
	if (a >= c && b >= c) {
		println("First")
	} else {
		println("Second")
	}
}

