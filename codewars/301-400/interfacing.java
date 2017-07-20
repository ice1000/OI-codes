import java.util.*;
import java.lang.reflect.*;

/**
 * Created by ice1000 on 17-7-3.
 *
 * @author ice1000
 */
public class Interfacing implements InvocationHandler {
		Map<String, Object> map = new HashMap<>();

		public static Object create(Class<?>[] interfaces) {
				return Proxy.newProxyInstance(interfaces[0].getClassLoader(), interfaces, new Interfacing());
		}

		@Override
		public Object invoke(Object o, Method method, Object[] objects) throws Throwable {
				if (method.getName().startsWith("set")) map.put(method.getName().substring(3), objects[0]);
				else return map.get(method.getName().substring(3));
				return null;
		}
}
