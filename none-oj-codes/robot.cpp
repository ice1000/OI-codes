#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <limits>

char command[5000];
long long t;
int que_len, len, i, j, times;
long long x, y, a, b;

int main(int argc, char* argv[]) {
	freopen("robot.in", "r", stdin);
	freopen("robot.out", "w", stdout);
	std::cin >> command >> t;
	len = strlen(command);
	que_len = t % len;
	times = t / len;
	// E -> N -> S -> W
	std::sort(command, command + que_len - 1);
	i = 0;
	while (command[i] == 'E') ++x, ++i;
	while (command[i] == 'N' && i < que_len) ++y, ++i;
	while (command[i] == 'S' && i < que_len) --y, ++i;
	while (command[i] == 'W' && i < que_len) --x, ++i;

//	std::cout<<len<<" "<<que_len<<" "<<i<<"\n";

	std::sort(command + que_len, command + len);
	while (command[i] == 'E') ++a, ++i;
	while (command[i] == 'N') ++b, ++i;
	while (command[i] == 'S') --b, ++i;
	while (command[i] == 'W') --a, ++i;

//	std::cout<<command<<std::endl;

//	std::cout << x << " " << y << " " << a << " " << b << " " << times << std::endl;

	std::cout << x * (times + 1) + a * times << ' ' << y * (times + 1) + b * times << std::endl;
	return 0;
}

/*
NSWWNSNEEWN
12
*/
