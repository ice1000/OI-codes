#include <stdio.h>
char map[101][101];

int n, k, x1, y1, x2, y2, can;

void aStar(int x, int y) {
  if (can) return ;
  if (x == x2 and y == y2) {
    ++can;
    return ;
  }
  if (x < 0 or y < 0 or x >= n or y >= n or map[x][y] == '#') return ;

  int xx, yy;
  if (x - x2) xx = x + x > x2 ? -1 : 1;
  if (y - y2) yy = y + y > y2 ? -1 : 1;
  aStar(xx, yy);
  if (!can and xx - x) {
    xx = x + x - xx;
    aStar(xx, y);
  } else {
    aStar(x - 1, y);
    aStar(x + 1, y);
  }
  if (!can and yy - y) {
    yy = y + y - yy;
    aStar(x, yy);
  } else {
    aStar(x, y + 1);
    aStar(x, y - 1);
  }

}

int main(int argc, char *argv[]) {
  int i, j;
  scanf("%i", &k);
  while (k--) {
    scanf("%i", &n);
    for (i = 0; i < n; ++i) scanf("%s", map[i]);
    scanf("%i %i %i %i", &x1, &y1, &x2, &y2);
    can = 0;
    aStar(x1, y1);
    if (can) printf("YES\n");
    else printf("NO\n");
  }
  return 0;
}

/**
2
3
.##
..#
#..
0 0 2 2
5
.....
###.#
..#..
###..
...#.
0 0 4 0
*/
