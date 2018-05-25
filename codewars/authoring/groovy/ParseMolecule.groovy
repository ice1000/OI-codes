import java.util.regex.Matcher
import java.util.regex.Pattern

class ParseMolecule {
    private static Iterator<String> tokenIter
    private static Stack<Integer> bracketStk

    private static final String AT_NUM = "[A-Z][a-z]?\\d*"
    private static final String OPEN_BRA = "[{(\\[]"
    private static final String CLOSE_BRA = "[)}\\]]\\d*"
    private static final Pattern TOKENIZER = Pattern.compile(String.format("%s|%s|%s", AT_NUM, OPEN_BRA, CLOSE_BRA))
    private static final Pattern P_AT_NUM = Pattern.compile("(?<at>[A-Z][a-z]*)(?<num>\\d*)")

    static Map<String, Integer> getAtoms(String formula) {
        List<String> tokens = new ArrayList<String>()
        Matcher m = TOKENIZER.matcher(formula)
        while (m.find()) tokens.add(m.group())

        if (String.join("", tokens) != formula) throw new IllegalArgumentException("Invalid formula")

        bracketStk = new Stack<Integer>()
        tokenIter = tokens.iterator()

        RawForm ans = getRawFormula()
        if (!bracketStk.empty()) throw new IllegalArgumentException("Invalid formula")

        return ans
    }


    static RawForm getRawFormula() {
        RawForm raw = new RawForm()
        while (tokenIter.hasNext()) {
            String tok = tokenIter.next()

            if (tok.matches(OPEN_BRA)) {
                bracketStk.push((int) tok.charAt(0))
                raw.concatWith(getRawFormula())

            } else if (tok.matches(AT_NUM)) {
                Matcher m = P_AT_NUM.matcher(tok)
                m.find()
                raw.addAtom(m.group("at"), m.group("num").isEmpty() ? 1 : Integer.parseInt(m.group("num")))

            } else if (tok.matches(CLOSE_BRA)) {
                if (bracketStk.empty() || (bracketStk.peek() + 1 != (int) tok.charAt(0) && bracketStk.peek() + 2 != (int) tok.charAt(0)))
                    throw new IllegalArgumentException("Invalid formula")
                bracketStk.pop()

                if (tok.length() > 1) raw.mulBy(Integer.parseInt(tok.substring(1)))
                break
            }
        }
        return raw
    }

    static class RawForm extends HashMap<String, Integer> {
        void addAtom(final String atom, final int n) { this.put(atom, n + this.getOrDefault(atom, 0)) }

        RawForm mulBy(final int n) { this.forEach { at, v -> this.put(at, v * n) }; return this }

        RawForm concatWith(RawForm other) {
            other.forEach { at, v -> this.put(at, v + this.getOrDefault(at, 0)) }; return this
        }
    }
}