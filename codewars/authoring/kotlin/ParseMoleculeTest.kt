import org.junit.Assert.assertEquals
import org.junit.Test
import org.junit.runner.RunWith
import org.junit.runners.Parameterized
import org.junit.runners.Parameterized.Parameters
import java.util.*
import kotlin.test.assertFailsWith

@RunWith(Parameterized::class)
class SolutionTest(atoms: List<String>, nums: List<Int>, private val formula: String, private val name: String) {
	private val expected: Map<String, Int>

	init {
		val exp = HashMap<String, Int>()
		for (i in atoms.indices) exp[atoms[i]] = nums[i]
		this.expected = exp
	}

	@Test
	fun testMolecule() {
		if (expected.isEmpty()) assertFailsWith<IllegalArgumentException>(String.format("Your function should throw an IllegalArgumentException for a wrong formula: %s", formula)) {
			getAtoms(formula)
		} else assertEquals(String.format("Should parse %s: %s", name, formula), expected, getAtoms(formula))
	}

	companion object {
		@Parameters
		@JvmStatic
		fun data(): List<Array<out Any>> =
				listOf(arrayOf(listOf("H", "O"), listOf(2, 1), "H2O", "water"),
						arrayOf(listOf("B", "H"), listOf(2, 6), "B2H6", "dihydroboran"),
						arrayOf(listOf("C", "H", "O"), listOf(6, 12, 6), "C6H12O6", "glucose"),
						arrayOf(listOf("C", "Mo", "O"), listOf(6, 1, 6), "Mo(CO)6", "molybdenum hexacarbonyl"),
						arrayOf(listOf("Mg", "H", "O"), listOf(1, 2, 2), "Mg(OH)2", "magnesium hydroxide"),
						arrayOf(listOf("C", "H", "Fe"), listOf(10, 10, 1), "Fe(C5H5)2", "ferrocene"),
						arrayOf(listOf("C", "H", "Fe", "O"), listOf(8, 8, 1, 2), "(C5H5)Fe(CO)2CH3", "cyclopentadienyliron dicarbonyl dimer"),
						arrayOf(listOf("Pd", "C", "H", "P"), listOf(1, 72, 60, 4), "Pd[P(C6H5)3]4", "tetrakis(triphenylphosphine)palladium(0)"),
						arrayOf(listOf("K", "O", "N", "S"), listOf(4, 14, 2, 4), "K4[ON(SO3)2]2", "Fremy's salt"),
						arrayOf(listOf("As", "Be", "C", "B", "Co", "O", "Cu"), listOf(2, 16, 44, 8, 24, 48, 5), "As2{Be4C5[BCo3(CO2)3]2}4Cu5", "really weird molecule"),
						arrayOf(listOf("Co", "N", "H", "O", "S"), listOf(4, 12, 42, 18, 3), "{[Co(NH3)4(OH)2]3Co}(SO4)3", "hexol sulphate"),
						arrayOf(listOf("C", "H", "O"), listOf(4, 4, 4), "C2H2(COOH)2", "maleic acid"),
						arrayOf(listOf("H", "O"), listOf(2, 1), "{((H)2)[O]}", "evilized water molecula"),
						arrayOf(emptyList<String>(), emptyList<Int>(), "pie", ""),
						arrayOf(emptyList<String>(), emptyList<Int>(), "Mg(OH", ""),
						arrayOf(emptyList<String>(), emptyList<Int>(), "MgOH)2", ""),
						arrayOf(emptyList<String>(), emptyList<Int>(), "Mg(OH]2", ""),
						arrayOf(emptyList<String>(), emptyList<Int>(), "Au5(C2H5[OH)3Li]3", ""))
	}
}