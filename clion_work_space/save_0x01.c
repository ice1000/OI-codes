#include <stdio.h>
#include <stdlib.h>

const int maxSize = 100000;
long counter = 0;

void merge(int *source, int startIndex, int midIndex, int endIndex) {
	int *temp = (int *) malloc(maxSize * sizeof(int));
	int i = startIndex;
	int j = midIndex + 1;
	// 双方都没完，合并两者
	int k;
	for(k = startIndex; i <= midIndex && j <= endIndex; k++) {
		if (source[i] > source[j]) {
			temp[k] = source[j];
			counter += (i - startIndex);
			j++;
		}
		else {
			temp[k] = source[i];
			i++;
		}
	}
	// 捡漏，其中一边合并完了。
	// 把剩下的粘上去。
	// 两种只可能执行其中一个，在边缘情况中出现
	while(i <= midIndex)
		temp[k++] = source[i++];
	while(j <= endIndex)
		temp[k++] = source[j++];
	// 把草稿粘给源
	for(i = startIndex; i <= endIndex; i++)
		source[i] = temp[i];
	free(temp);
}

//内部使用递归
void mergeSort(int *sourceArr, int startIndex, int endIndex) {
	if(startIndex < endIndex) {
		int midIndex;
		midIndex = (startIndex + endIndex) / 2;
		mergeSort(sourceArr, startIndex, midIndex);
		mergeSort(sourceArr, midIndex + 1, endIndex);
		merge(sourceArr, startIndex, midIndex, endIndex);
	}
}

int main(int argc, char * argv[]) {
	int *a;
	int size;
	scanf("%i", &size);
	a = (int *)malloc(size * sizeof(int));
	int i;
	for(i = 0; i < size; i++)
		scanf("%i", &a[i]);
	mergeSort(a, 0, size - 1);
	printf("%li", counter);
	free(a);
	return 0;
}
/*
测试数据：
6
2 6 3 4 5 1

 => 8
 */
