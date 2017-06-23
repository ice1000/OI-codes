package codewars;

import codewars.PeanoNumbers.Peano.Succ;

import static codewars.PeanoNumbers.Ordering.*;
import static codewars.PeanoNumbers.Peano.Zero;

/**
 * !!MENTION!!
 * You can't use the following characters:
 * + - * / % > <
 * Created by ice1000 on 17-6-22.
 *
 * @author ice1000
 */
public final class PeanoNumbers {
	interface Peano {
		final class Zero implements Peano {
			static Zero INSTANCE = new Zero();

			private Zero() {
			}
		}

		final class Succ implements Peano {
			final Peano peano;

			Succ(Peano peano) {
				this.peano = peano;
			}
		}
	}

	enum Ordering {GT, LT, EQ}

	static Peano add(Peano a, Peano b) {
		if (a instanceof Zero) return b;
		if (b instanceof Zero) return a;
		return add(new Succ(a), ((Succ) b).peano);
	}

	/**
	 * @throws ArithmeticException if return value is negative
	 *                             message should be 'negative number'
	 */
	static Peano sub(Peano a, Peano b) {
		if (b instanceof Zero) return a;
		if (a instanceof Zero) throw new ArithmeticException("negative number");
		return sub(((Succ) a).peano, ((Succ) b).peano);
	}

	static Peano mul(Peano a, Peano b) {
		if (a instanceof Zero) return a;
		if (b instanceof Zero) return b;
		return add(a, mul(a, ((Succ) b).peano));
	}

	/**
	 * @throws ArithmeticException if divided by 0
	 *                             message should be 'divide by 0'
	 */
	static Peano div(Peano a, Peano b) {
		if (b instanceof Zero) throw new ArithmeticException("divide by 0");
		if (a instanceof Zero) return a;
		switch (compare(a, b)) {
			case EQ:
				return new Succ(Zero.INSTANCE);
			case LT:
				return Zero.INSTANCE;
			case GT:
			default:
				return new Succ(div(sub(a, b), b));
		}
	}

	static boolean even(Peano peano) {
		return peano instanceof Zero || !(((Succ) peano).peano instanceof Zero)
				&& odd(((Succ) peano).peano);
	}

	static boolean odd(Peano peano) {
		return !even(peano);
	}

	static Ordering compare(Peano a, Peano b) {
		boolean x = a instanceof Zero;
		boolean y = b instanceof Zero;
		return x ? y ? EQ : LT : y ? GT : compare(((Succ) a).peano, ((Succ) b).peano);
	}
}
