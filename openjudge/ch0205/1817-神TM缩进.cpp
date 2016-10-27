#include <stdio.h>
#include <string.h>
#include <queue>

const int size = 50;

typedef struct Room {
/**/bool north;
/**/bool south;
/**/bool east;
/**/bool west;

/**/Room(int s = 0) {
/**//**/north = (bool) (s & 0b0010);
/**//**/south = (bool) (s & 0b1000);
/**//**/east = (bool) (s & 0b0100);
/**//**/west = (bool) (s & 0b0001);
/**/}
} Room;

typedef struct Poi {
/**/int x;
/**/int y;

/**/Poi(int _x = 0, int _y = 0) : x(_x), y(_y) { }
} Poi;

Room a[size][size];
bool b[size][size];

int main(int argc, char *argv[]) {
/**/int y, x, s;
/**/scanf("%i %i", &x, &y);
/**/memset(b, false, sizeof(b));

/**/for (int i = 0; i < x; i++)
/**//**/for (int j = 0; j < y; j++) {
/**//**//**/scanf("%i", &s);
/**//**//**/a[i][j] = Room(s);
/**//**/}
/**/int max = 0;
/**/int cnt = 0;

/**/std::queue<Poi> q = *new std::queue<Poi>;
/**/while (!q.empty()) q.pop();

/**/while (true) {
/**//**/int this_max = 1;

/**//**/int loop = 0;
/**//**/for (int i = 0; i < x; i++)
/**//**//**/for (int j = 0; j < y; j++)
/**//**//**//**/if (b[i][j]) ++loop;
/**//**/if (loop >= y * x) break;
/**//**/++cnt;
/**//**/bool loop_ = true;
/**//**/if (q.empty()) {
/**//**//**/for (int i = 0; i < x && loop_; i++)
/**//**//**//**/for (int j = 0; j < y; j++)
/**//**//**//**//**/if (!b[i][j]) {
/**//**//**//**//**//**/b[i][j] = true, q.push(*new Poi(i, j)), loop_ = false;
/**//**//**//**//**//**/break;
/**//**//**//**//**/}
/**//**/}

/**//**/while (!q.empty()) {
/**//**//**/Poi p = q.front();
/**//**//**/q.pop();
/**//**//**/if (!a[p.x][p.y].east && !b[p.x][p.y + 1]) p.y++, b[p.x][p.y] = true, this_max++, q.push(p), p.y--;
/**//**//**/if (!a[p.x][p.y].west && !b[p.x][p.y - 1]) p.y--, b[p.x][p.y] = true, this_max++, q.push(p), p.y++;
/**//**//**/if (!a[p.x][p.y].south && !b[p.x + 1][p.y]) p.x++, b[p.x][p.y] = true, this_max++, q.push(p), p.x--;
/**//**//**/if (!a[p.x][p.y].north && !b[p.x - 1][p.y]) p.x--, b[p.x][p.y] = true, this_max++, q.push(p);
/**//**/}
/**//**/if (this_max > max) max = this_max;
/**/}
/**/printf("%i\n%i", cnt, max);
/**/return 0;
}

