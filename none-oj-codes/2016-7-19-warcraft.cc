#include <stdio.h>
#include <queue>
using namespace std;

typedef struct {
	int step;
	int boss_hp;
	int player_mp;
} node ;

struct {
	int use;
	int fuck;
} weapon[1001];

int main(int argc, char *argv[]) {
	freopen("warcraft.in", "r", stdin );
	freopen("warcraft.out","w+",stdout);
	int n, t, k, i, j;
	queue<node> q;
	weapon[0].use = 0;
	weapon[0].fuck = 1;
	bool won = false;
	int hp_backup;
	int mp_backup;
	while(scanf("%i %i %i", &n, &t, &k)) {
		if(!n && !t && !k) break;
		while(!q.empty()) q.pop();
		// skipping the first(it was A)
		n++;
		won = false;
		for(i = 1; i < n; i++)
			scanf("%i %i", &weapon[i].use, &weapon[i].fuck);
		node no;
		no.boss_hp = 100;
		no.player_mp = 100;
		no.step = 0;
		q.push(no);
		// BFS
		while(!q.empty() && !won) {
			no = q.front();
			no.step++;
			q.pop();
			for(i = 0; i < n; i++) {
				if(no.player_mp >= weapon[i].use) {
					hp_backup = no.boss_hp;
					mp_backup = no.player_mp;
					no.boss_hp -= weapon[i].fuck;
					no.player_mp += t - weapon[i].use;
					if(no.player_mp > 100) no.player_mp = 100;
//					printf("mp = %d, boss = %d, step = %d\n", no.player_mp, no.boss_hp, no.step);
					if(no.boss_hp <= 0) {
						won = true;
						printf("%d\n", no.step);
						break;
					}
					q.push(no);
					no.boss_hp = hp_backup;
					no.player_mp = mp_backup;
				}
			}
			if(no.step * k >= 100) break;
		}
		if(!won) printf("My god\n");
	}
	return 0;
}
/*
4 2 25
10 5
20 10
30 28
76 70
4 2 25
10 5
20 10
30 28
77 70
0 0 0
*/
