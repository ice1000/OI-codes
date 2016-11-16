//NOIP 2016 UKHH GMIJ CQWY QIIZ PFJM DAY 1
//YTYZ SADW BBBB chess.cpp/c/pas
//Time Limit : 2000 MS
//Memory Limit : 128 M
//LDNU IPWK - Enrong
#include <stdio.h>
#include <list>
#include <map>

using namespace std;

int n, k, ans;
char ma[15][15];
bool maa[15][15];
bool book[15][15];

void dfs(int x, int y, int step)
{
	if (step == k)
	{
		ans++;
		return;
	}
	for (int i = 0; i < n; ++i)
	{
		book[x][i] = false;
		book[i][y] = false;
	}
	for (int i = x + 1; i < n - k + step + 1; ++i)
		for (int j = 0; j < n; ++j)
		{
			if (book[i][j])
				dfs(i, j, step + 1);
		}
	for (int i = 0; i < n; ++i)
	{
		book[x][i] = maa[x][i];
		book[i][y] = maa[i][y];
	}
	return;
}

int main()
{
	freopen("chess.in", "r", stdin);
	freopen("chess.out", "w", stdout);
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; ++i)
		scanf("%s", ma[i]);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
		{
			maa[i][j] = ma[i][j] == '#';
			book[i][j] = maa[i][j];
		}
	for (int m = 0; m < n - k + 1; ++m)
		for (int o = 0; o < n; ++o)
		{
			if (maa[m][o])
				dfs(m, o, 1);
		}
	printf("%d\n", ans);
	return 0;
}

