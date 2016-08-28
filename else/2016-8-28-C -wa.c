#include <stdio.h>

int bucket[100002];
int reward[100002];

int dick = 0;

int findMaxReward() {
	int i, maxIndex = 1;
	for (i = 1; i <= dick; ++i) if (reward[i] > reward[maxIndex]) maxIndex = i;
	return maxIndex;
}

int findBullet() {
	int i, maxIndex = 1;
	for (i = 1; i <= dick; ++i) if (bucket[i] > bucket[maxIndex]) maxIndex = i;
	return maxIndex;
}

int main(int argc, char* argv[]) {
	int n, i, m, score = 0, fuck;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) {
		scanf("%d", &m);
		if (m > dick) dick = m;
		if (!bucket[m]) fuck++;
		bucket[m]++;
		reward[m] += m;
		reward[m - 1] -= m;
		reward[m + 1] -= m;
	}
	while (fuck) {
		m = findMaxReward();
		fuck--;
		if (bucket[m - 1]) fuck--;
		if (bucket[m + 1]) fuck--;
		score += bucket[m] * m;
		reward[m - 2] += bucket[m - 1] * (m - 1);
		reward[m + 2] += bucket[m + 1] * (m + 1);
		bucket[m] = bucket[m - 1] = bucket[m + 1] = reward[m] = reward[m - 1] = reward[m + 1] = 0;
	}
	printf("%d", score);
	return 0;
}
