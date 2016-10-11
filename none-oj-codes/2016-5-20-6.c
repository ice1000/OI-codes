#include <stdio.h>

int reg_match(int i, int j, char* r, char* s) {
	// 边界判断
	if(!r[i] || !s[j]) {
		// 两个都到头了
		if(!r[i] && !s[j]) return 1;
		// 匹配式已经到头了，但是正则式可能还有多余的*，在这里处理这种情况。
		else if(r[i] == '*') return reg_match(++i, j, r, s);
		// 如果还是不能匹配那就尴尬了。
		else return 0;
	}
	// 移动到下一个字符。
	i++, j++;
	if(r[i] == '?')
		// 单字符匹配，无论如果都过。
		return reg_match(i, j, r, s);
	else if(r[i] == '*') {
		// 这是DFS核心代码
  		for(; s[j]; j++)
			// *匹配从0个开始到全部匹配结束，一旦返回了1就直接返回了，没有的话继续
			// 到最后就放弃治疗
  			if(reg_match(i, j, r, s)) return 1;
		return 0;
	}
	// 匹配成功
	else if(r[i] == s[i]) return reg_match(i, j, r, s);
	// 匹配失败，直接处刑
	else reg_match(i, j, r, s);
}

int main(int argc, char* argv[]) {
	int i = 0, j = 0;
	char reg[0xfff], sam[0xfff];
	scanf("%s%s", reg, sam);
	printf(reg_match(0, 0, reg, sam) ? "matched" : "not matched");
	return 0;
}
