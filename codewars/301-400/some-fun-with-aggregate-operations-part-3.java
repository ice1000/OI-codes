import java.util.*;
import java.util.stream.*;

/**
 * Created by ice1000 on 17-7-3.
 *
 * @author ice1000
 */
public class AggregationKata {
		public static Map<String, List<String>> getStudentNamesByDepartment(Stream<Student> students) {
				return students
						.collect(Collectors
										 .groupingBy(Student::getDepartment, Collectors
																 .mapping(Student::getName, Collectors.toList())));
		}
}
