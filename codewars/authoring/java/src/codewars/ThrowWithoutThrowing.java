package codewars;

import java.awt.*;
import java.nio.ByteBuffer;
import java.util.*;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * Created by ice1000 on 17-6-16.
 *
 * @author ice1000
 */
/*
import java.awt.*;
import java.nio.ByteBuffer;
import java.util.*;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class ThrowWithoutThrowing {
	public static void arrayIndexOutOfBound() {
	}

	public static void negativeArraySize() {
	}

	public static void noSuchElement() {
	}

	public static void arithmetic() {
	}

	public static void classCast() {
	}

	public static void stackOverflow() {
	}

	public static void nullPointer() {
	}

	public static void numberFormat() {
	}

	public static void illegalArgument() {
	}

	public static void emptyStack() {
	}

	public static void bufferOverflow() {
	}

	public static void arrayStore() {
	}

	public static void unsupportedOperation() {
	}

	public static void illegalState() {
	}
}
*/
public class ThrowWithoutThrowing {
	public static void arrayIndexOutOfBound() {
		int[] a = new int[]{666};
		System.out.println(a[233]);
	}

	public static void negativeArraySize() {
		int[] a = new int[-100];
	}

	public static void noSuchElement() {
		new ArrayList<Void>().iterator().next();
	}

	public static void arithmetic() {
		//noinspection NumericOverflow
		System.out.println(233_666 / 0);
	}

	public static void classCast() {
		System.out.println((Set) new ArrayList<>(1));
	}

	public static void stackOverflow() {
		stackOverflow();
	}

	public static void nullPointer() {
		String i = null;
		System.out.println(i.equals("ice1000"));
	}

	public static void numberFormat() {
		Integer.parseInt("ice1000");
	}

	public static void illegalArgument() {
		new Color(-1, -1, 0xFFF);
	}

	public static void emptyStack() {
		new Stack<Void>().pop();
	}

	public static void bufferOverflow() {
		ByteBuffer.allocate(0).put((byte) 10);
	}

	public static void arrayStore() {
		Object[] a = new String[1];
		a[0] = 1;
	}

	public static void unsupportedOperation() {
		List<String> list1 = new ArrayList<>();
		list1.add("test");
		String[] array = new String[2];
		List list2 = Arrays.asList(array);
		List<String> list3 = new ArrayList<>(list2);
		list3.add("test");
		array[0] = "test2";
		list2.add("test");
	}

	public static void illegalState() {
		Stream<String> introStream = Stream.of(
				"Get started with UICollectionView and the photo library".split(" "));
		Map<Integer, String> introMap2 = introStream.collect(Collectors.toMap(String::length,
				s -> s));
	}
}

