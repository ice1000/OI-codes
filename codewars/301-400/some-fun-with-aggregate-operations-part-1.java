import java.util.*;
import java.util.stream.*;
import java.util.function.Supplier;

/**
 * Created by ice1000 on 17-7-3.
 *
 * @author ice1000
 */
public class AggregationKata {
		public static Map<String, Double> getAverageGradeByDepartment(Student[] students) {
				Map<String, Double> ret = new HashMap<>();
				Supplier<Stream<Student>> supplier = () -> Arrays.stream(students);
				supplier.get().map(Student::getDepartment).distinct().forEach
						(dep -> ret.put(dep, supplier.get().filter
														(stu -> Objects.equals(stu.getDepartment(), dep)).mapToDouble
														(Student::getGrade).average().orElse(0)));
				return ret;
		}
}
