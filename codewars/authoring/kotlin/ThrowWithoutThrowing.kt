import java.awt.Color
import java.nio.ByteBuffer
import java.util.*
import java.util.concurrent.ArrayBlockingQueue

/**
 * Created by ice1000 on 17-6-16.
 *
 * @author ice1000
 */


fun arrayIndexOutOfBound() {
	val a = intArrayOf(666)
	println(a[233])
}

fun negativeArraySize() {
	IntArray(-100)
}

fun noSuchElement() {
	listOf<Nothing>().iterator().next()
}

fun arithmetic() {
	println(233666 / 0)
}

fun classCast() {
	println(ArrayList<Any>(1) as Set<*>)
}

fun stackOverflow() {
	stackOverflow()
}

fun nullPointer() {
	null!!
}

fun numberFormat() {
	Integer.parseInt("ice1000")
}

fun illegalArgument() {
	Color(-1, -1, 0xFFF)
}

fun emptyStack() {
	Stack<Void>().pop()
}

fun bufferOverflow() {
	ByteBuffer.allocate(0).put(10.toByte())
}

@Suppress("UNCHECKED_CAST")
fun arrayStore() {
	val a: Array<Any> = arrayOf("") as Array<Any>
	a[0] = 1
}

fun unsupportedOperation() {
	val list1 = ArrayList<String>()
	list1.add("test")
	val array = arrayOfNulls<String>(2)
	val list2 = Arrays.asList<String>(*array)
	val list3 = ArrayList(list2)
	list3.add("test")
	array[0] = "test2"
	list2.add("test")
}

fun illegalState() {
	val queue = ArrayBlockingQueue<Int>(1)
	queue.add(1)
	queue.add(1)
}


