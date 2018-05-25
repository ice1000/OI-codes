import org.junit.Test
import org.junit.runner.RunWith
import org.junit.runners.Parameterized

import static org.junit.Assert.assertEquals
import static org.junit.Assert.assertTrue

@RunWith(Parameterized.class)
class SolutionTest {
    private Map<String, Integer> expected
    private String formula, name

    public SolutionTest(List<String> atoms, List<Integer> nums, String formula, String name) {
        Map<String, Integer> exp = new HashMap<String, Integer>()
        for (int i = 0; i < atoms.size(); i++) exp.put(atoms.get(i), nums.get(i))

        this.expected = exp
        this.formula = formula
        this.name = name
    }

    @Test
    void testMolecule() {
        if (expected.isEmpty()) {
            boolean isGood = false
            try {
                ParseMolecule.getAtoms(formula)
            } catch (IllegalArgumentException ignored) {
                isGood = true
            } finally {
                assertTrue(String.format("Your function should throw an IllegalArgumentException for a wrong formula: %s", formula), isGood)
            }

        } else
            assertEquals(String.format("Should parse %s: %s", name, formula), expected, ParseMolecule.getAtoms(formula))
    }

    @Parameterized.Parameters
    static Collection<Object[]> data() {
        Arrays.asList(
                [Arrays.asList("H", "O"), Arrays.asList(2, 1), "H2O", "water"].toArray(new Object[0]),
                [Arrays.asList("B", "H"), Arrays.asList(2, 6), "B2H6", "dihydroboran"].toArray(new Object[0]),
                [Arrays.asList("C", "H", "O"), Arrays.asList(6, 12, 6), "C6H12O6", "glucose"].toArray(new Object[0]),
                [Arrays.asList("C", "Mo", "O"), Arrays.asList(6, 1, 6), "Mo(CO)6", "molybdenum hexacarbonyl"].toArray(new Object[0]),
                [Arrays.asList("Mg", "H", "O"), Arrays.asList(1, 2, 2), "Mg(OH)2", "magnesium hydroxide"].toArray(new Object[0]),
                [Arrays.asList("C", "H", "Fe"), Arrays.asList(10, 10, 1), "Fe(C5H5)2", "ferrocene"].toArray(new Object[0]),
                [Arrays.asList("C", "H", "Fe", "O"), Arrays.asList(8, 8, 1, 2), "(C5H5)Fe(CO)2CH3", "cyclopentadienyliron dicarbonyl dimer"].toArray(new Object[0]),
                [Arrays.asList("Pd", "C", "H", "P"), Arrays.asList(1, 72, 60, 4), "Pd[P(C6H5)3]4", "tetrakis(triphenylphosphine)palladium(0)"].toArray(new Object[0]),
                [Arrays.asList("K", "O", "N", "S"), Arrays.asList(4, 14, 2, 4), "K4[ON(SO3)2]2", "Fremy's salt"].toArray(new Object[0]),
                [Arrays.asList("As", "Be", "C", "B", "Co", "O", "Cu"), Arrays.asList(2, 16, 44, 8, 24, 48, 5), "As2{Be4C5[BCo3(CO2)3]2}4Cu5", "really weird molecule"].toArray(new Object[0]),
                [Arrays.asList("Co", "N", "H", "O", "S"), Arrays.asList(4, 12, 42, 18, 3), "{[Co(NH3)4(OH)2]3Co}(SO4)3", "hexol sulphate"].toArray(new Object[0]),
                [Arrays.asList("C", "H", "O"), Arrays.asList(4, 4, 4), "C2H2(COOH)2", "maleic acid"].toArray(new Object[0]),
                [Arrays.asList("H", "O"), Arrays.asList(2, 1), "{((H)2)[O]}", "evilized water molecula"].toArray(new Object[0]),
                [Collections.emptyList(), Collections.emptyList(), "pie", ""].toArray(new Object[0]),
                [Collections.emptyList(), Collections.emptyList(), "Mg(OH", ""].toArray(new Object[0]),
                [Collections.emptyList(), Collections.emptyList(), "MgOH)2", ""].toArray(new Object[0]),
                [Collections.emptyList(), Collections.emptyList(), "Mg(OH]2", ""].toArray(new Object[0]),
                [Collections.emptyList(), Collections.emptyList(), "Au5(C2H5[OH)3Li]3", ""].toArray(new Object[0]))
    }
}
