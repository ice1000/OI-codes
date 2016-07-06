#include <cstring>
#include <cstdio>

class BigInt {
public:
	const static int max_size = 9999;
	char value[max_size];
	int len = 0;

	BigInt(const char* source) {
		memset(value, '0', max_size);
		strcpy(value, source);
		len = (int) strlen(source);
	}

	bool operator==(const BigInt &other) const {
		if (this->len != other.len) return false;
		for (int i = 0; i < len; i++)
			if (this->value[i] != other.value[i])
				return false;
		return true;
	}

	bool operator>(const BigInt &other) const {
		if (this->len > other.len) return true;
		if (this->len < other.len) return false;
		for (int i = 0; i < len; i++)
			if (this->value[i] > value[i])
				return true;
		return false;
	}

	bool operator<=(const BigInt &other) const {
		return !(*this > other);
	}

	bool operator<(const BigInt &other) const {
		return (*this <= other) && !(*this == other);
	}

	bool operator>=(const BigInt &other) const {
		return !(*this < other);
	}

	BigInt operator+(const BigInt &other) const {
		BigInt result("0");
	}
};

int main(int argc, char* argv[]) {
	BigInt bigInt("3927438967472384723047238947");
	BigInt bigInt1("983829048230948923");
	printf("%d", bigInt > bigInt1 ? 1 : 0);
	return 0;
}
