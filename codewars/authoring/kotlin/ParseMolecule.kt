import java.util.*
import java.util.regex.*

private lateinit var tokenIter: Iterator<String>
private lateinit var bracketStk: Stack<Int>

private val AT_NUM = "[A-Z][a-z]?\\d*"
private val OPEN_BRA = "[{(\\[]"
private val CLOSE_BRA = "[)}\\]]\\d*"
private val TOKENIZER = Pattern.compile(String.format("%s|%s|%s", AT_NUM, OPEN_BRA, CLOSE_BRA))
private val P_AT_NUM = Pattern.compile("(?<at>[A-Z][a-z]*)(?<num>\\d*)")

private val rawFormula: RawForm
	get() {
		val raw = RawForm()

		while (tokenIter.hasNext()) {
			val tok = tokenIter.next()

			if (tok.matches(OPEN_BRA.toRegex())) {
				bracketStk.push(tok[0].toInt())
				raw.concatWith(rawFormula)

			} else if (tok.matches(AT_NUM.toRegex())) {
				val m = P_AT_NUM.matcher(tok)
				m.find()
				raw.addAtom(m.group("at"), if (m.group("num").isEmpty()) 1 else Integer.parseInt(m.group("num")))

			} else if (tok.matches(CLOSE_BRA.toRegex())) {
				if (bracketStk.empty() || bracketStk.peek() + 1 != tok[0].toInt() && bracketStk.peek() + 2 != tok[0].toInt())
					throw IllegalArgumentException("Invalid formula")
				bracketStk.pop()

				if (tok.length > 1) raw.mulBy(Integer.parseInt(tok.substring(1)))
				break
			}
		}
		return raw
	}

fun getAtoms(formula: String): Map<String, Int> {
	val tokens = ArrayList<String>()
	val m = TOKENIZER.matcher(formula)
	while (m.find()) tokens.add(m.group())
	if (tokens.joinToString("") != formula) throw IllegalArgumentException("Invalid formula")
	bracketStk = Stack()
	tokenIter = tokens.iterator()

	val ans = rawFormula
	if (!bracketStk.empty()) throw IllegalArgumentException("Invalid formula")

	return ans
}

internal class RawForm : HashMap<String, Int>() {
	fun addAtom(atom: String, n: Int) {
		this[atom] = n + getOrDefault(atom, 0)
	}

	fun mulBy(n: Int): RawForm {
		this.forEach { at, v -> this[at] = v * n }
		return this
	}

	fun concatWith(other: RawForm): RawForm {
		other.forEach { at, v -> this[at] = v + getOrDefault(at, 0) }
		return this
	}
}
