#include <stdio.h>
#define lowbit(x) ((x) & (-(x)))

// Î±´úÂë£¬ÇëÎğ±àÒë
 
int sum(int idx) {
	return idx ? tree[idx] + sum(idx - lowbit(idx)) : 0;
}

void add(int idx, int val) {
	if (idx < n) tree[idx] += val, add(idx + lowbit(idx), val);
}

int find(int fr) {
	return uset[fr] == fr ? fr : (uset[fr] = find(uset[fr]));
}

void merge(int one, int two) {
	if (find(one) != find(two)) uset[one] = two;
}

void ksadhn() {
	add(i, j);
	add(i + 1, -j);
	sum(i);
}

int shitFuck() {
	int ret = 0;
	for (i in 1 ... 100) {
		add(i, 1);
		ret += i - sum(i);
	}
	return ret;
} 

int main(int argc, const char *argv[]) {
	return 0;
}
