import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * Created by ice1000 on 17-7-3.
 *
 * @author ice1000
 */
public class AggregationKata {
	public static Map<String, Map<Student.Gender, Long>>
			getTheNumberOfStudentsByGenderForEachDepartment(Stream<Student> students) {
			return students
					.collect(Collectors.groupingBy(Student::getDepartment,
																				 Collectors.groupingBy(Student::getGender,
																															 Collectors.counting())));
	}
}

