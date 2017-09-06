import java.util.HashMap
import java.util.HashSet

private fun generateRegex(n: Int): String {
	if (n == 1) return "1[01]*"
	val states = HashSet<Int>()
	states += 0 until n
	val dfa = DFA(states, 0, arrayOf(0))
	for (i in 0 until n) {
		dfa.addTransition(i, i * 2 % n, "0")
		dfa.addTransition(i, (i * 2 + 1) % n, "1")
	}
	return dfa.reduce()
}

fun regexDivisibleBy(n: Int): String {
	var n = n
	val start = "^(0|"
	var end = ")$"
	while (n % 2 == 0) {
		end = "0" + end
		n /= 2
	}
	return String.format("%s%s%s", start, generateRegex(n), end)
}

internal class Transition(var from: Int, var to: Int) : Comparable<Transition> {
	override fun equals(other: Any?): Boolean {
		if (other is Transition) {
			val otherTrans = other as Transition?
			return this.from == otherTrans!!.from && this.to == otherTrans.to
		}
		return false
	}

	override operator fun compareTo(other: Transition): Int {
		val compare = this.from.compareTo(other.from)
		return if (compare == 0) this.to.compareTo(other.to) else compare
	}

	override fun toString(): String {
		return String.format("(from: %d, to: %d)", this.from, this.to)
	}
}

internal class DFA(private val states: MutableSet<Int>, startState: Int, acceptedStates: Array<Int>) {
	private val START_STATE = -1
	private val END_STATE = -2
	private val transitions: HashMap<Transition, String> = hashMapOf()

	init {
		this.addTransition(START_STATE, startState, "")
		for (acceptedState in acceptedStates) {
			this.addTransition(acceptedState, END_STATE, "")
		}
	}

	fun addTransition(from: Int, to: Int, transition: String) {
		this.transitions.put(Transition(from, to), transition)
	}

	private fun selectState(): Int {
		val fromCount = HashMap<Int, Int>()
		val toCount = HashMap<Int, Int>()
		for (transition in this.transitions.keys) {
			if (transition.from != transition.to) {
				var currentCount = (fromCount as MutableMap<Int, Int>).getOrDefault(transition.from, 0)
				fromCount.put(transition.from, currentCount + 1)
				currentCount = (toCount as MutableMap<Int, Int>).getOrDefault(transition.to, 0)
				toCount.put(transition.to, currentCount + 1)
			}
		}
		var minState = 0
		var minBranches = 999
		for (state in this.states) {
			val from = (fromCount as MutableMap<Int, Int>).getOrDefault(state, 0)
			val to = (toCount as MutableMap<Int, Int>).getOrDefault(state, 0)
			val branches = from * to
			if (branches < minBranches) {
				minState = state
				minBranches = branches
			}
		}
		return minState
	}

	private fun removeState(state: Int?) {
		val enteringTrans = HashMap<Int, String>()
		val exitingTrans = HashMap<Int, String>()
		var loop = ""
		var hasLoop = false
		var keys = HashSet(this.transitions.keys)
		for (trans in keys) {
			if (trans.from == trans.to && trans.from == state) {
				loop = this.transitions[trans]!!
				hasLoop = true
			} else if (trans.from == state) {
				exitingTrans.put(trans.to, this.transitions[trans]!!)
			} else if (trans.to == state) {
				enteringTrans.put(trans.from, this.transitions[trans]!!)
			}
			if (trans.from == state || trans.to == state) {
				this.transitions.remove(trans)
			}
		}
		if (hasLoop) {
			loop = String.format("(%s)*", loop)
		}
		for (enterState in enteringTrans.keys) {
			val enteringString = enteringTrans[enterState]
			for (exitState in exitingTrans.keys) {
				val exitingString = exitingTrans[exitState]

				var existingTrans: String? = null
				var hasExistingTrans = false
				keys = HashSet(this.transitions.keys)
				for (trans in keys) {
					if (trans.from == enterState && trans.to == exitState) {
						existingTrans = this.transitions[trans]
						hasExistingTrans = true
						this.transitions.remove(trans)
					}
				}

				var newTrans = String.format("%s%s%s", enteringString, loop, exitingString)
				if (hasExistingTrans) {
					newTrans = String.format("(%s|%s)", existingTrans, newTrans)
				}
				this.addTransition(enterState, exitState, newTrans)
			}
		}
		this.states.remove(state)
	}

	fun reduce(): String {
		while (this.states.size > 0) {
			val state = this.selectState()
			this.removeState(state)
		}
		var result = ""
		for (trans in this.transitions.keys) {
			result = this.transitions[trans]!!
		}
		return result
	}
}
