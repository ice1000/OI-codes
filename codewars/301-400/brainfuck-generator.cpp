#include <stdio.h>
#include <string>

inline std::string to_brainfuck(const std::string& s) {
	char ptr = '\0';
	auto ret = std::string();
	for (auto i = 0; i < s.length(); ++i) {
		while (ptr != s[i]) ret += '+', ptr++;
		ret += '.';
	}
	return ret;
}
