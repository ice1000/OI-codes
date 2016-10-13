/*
作者:千里冰封
题目:p1058 合唱队形
*/

#include <stdio.h>
#include <string.h>

#ifdef __max
#undef __max
#endif

#define __max(x, y) ((x) > (y) ? (x) : (y))

int a[1001];
int dp1[1001] = { 1 };
int dp2[1001] = { 1 };

int main(int argc, char *argv[]) {
  int n, i, j, max = 0;
  scanf("%i", &n);
  for (i = 0; i < n; ++i) {
    scanf("%i", &a[i]);
    dp1[i] = dp2[i] = 1;
  }
  for (i = 1; i < n; ++i) {
    for (j = 0; j < i; ++j) {
      if (a[i] > a[j] && dp1[j] + 1 > dp1[i])
        dp1[i] = __max(dp1[j] + 1, dp1[i]);
    }
  }
  for (i = n - 2; i >= 0; --i) {
    for (j = n - 1; j > i; --j) {
      if (a[i] > a[j] && dp2[j] + 1 > dp2[i])
        dp2[i] = __max(dp2[j] + 1, dp2[i]);
    }
  }
//  for (i = 0; i < n; ++i) printf("%i ", dp1[i]);
//  puts("");
//  for (i = 0; i < n; ++i) printf("%i ", dp2[i]);
//  puts("");
  for (i = 0; i < n; ++i) {
    max = __max(max, dp1[i] + dp2[i]);
  }
  printf("%i", n - max + 1);
  return 0;
}

/*
100
157 165 138 130 141 206 160 164 216 216 145 227 180 147 170 216 154 144 171 230 205 137 169 181 146 133 220 138 175 207 173 155 136 167 144 166 140 191 145 162 214 213 151 200 166 131 221 154 161 229 136 194 215 202 137 202 157 132 166 215 218 230 168 217 131 189 203 131 207 176 172 211 187 158 165 156 179 194 200 145 130 183 174 143 148 218 213 187 204 221 160 169 168 224 163 132 226 135 201 217


8
186 186 150 200 160 130 197 220
1 1 1 2 2 1 3 4
3 3 2 3 2 1 1 1
4
--------------------------------
Process exited after 6.17 seconds with return value 0
请按任意键继续. . .
*/
