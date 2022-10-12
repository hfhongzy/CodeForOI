#include <algorithm>
#include <cstdio>
using namespace std;
const int INF = 1e9 + 10, N = 504;
int n, m, T[N][N], G[N][N], cnt[N];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++) {
		fill(G[i] + 1, G[i] + n + 1, INF);
		G[i][i] = 0;
	}
	for(int u, v, w, i = 1; i <= m; i ++) {
		scanf("%d%d%d", &u, &v, &w);
		G[v][u] = G[u][v] = min(G[u][v], w);
	}
	for(int i = 1; i <= n; i ++)
		copy(G[i] + 1, G[i] + n + 1, T[i] + 1);
	for(int k = 1; k <= n; k ++)
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= n; j ++)
				G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
	for(int s = 1; s <= n; s ++) {
		fill(cnt + 1, cnt + n + 1, 0);
		for(int i = 1; i <= n; i ++) {
			for(int j = 1; j <= n; j ++) if(i != j && T[i][j] < INF) {
				if(G[s][i] + T[i][j] == G[s][j]) {
					cnt[j] ++;
				}
			}
		}
		for(int t = s + 1; t <= n; t ++) {
			int ans = 0;
			for(int p = 1; p <= n; p ++) if(p != s && G[s][p] + G[p][t] == G[s][t]) {
				ans += cnt[p];
			}
			printf("%d ", ans);
		}
	}
	return 0;
}
//d[u][v] = d[u][p0] + w + d[p1][v]
//d[u][v] = d[u][p] + d[p][v]