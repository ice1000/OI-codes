#include <algorithm>
#include <list>

using namespace std;

int findDeletedNumber(list<int> s, list<int> m) {
	s.sort();
	m.sort();
	while (!s.empty() && !m.empty()) {
		if (s.front() != m.front()) return s.front();
		s.pop_front();
		m.pop_front();
	}
  if (!s.empty()) return s.front();
	if (!m.empty()) return m.front();
	return 0;
}
