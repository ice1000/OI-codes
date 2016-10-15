import java.util.*

fun main(args: Array<String>) {
	var t = 0
	var n = 0
	val s = Scanner(System.`in`)
	for (i in 1..s.nextInt()) {
		n = s.nextInt();
		if (n > 2) println(n - 2)
		else println(0)
	}
}

