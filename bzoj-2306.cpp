#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
typedef double db;
const int N = 110;
int n, m, s;
db p, w[N], G[N][N][52];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++) scanf("%lf", w + i);
	scanf("%d%lf", &s, &p);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			fill(G[i][j], G[i][j] + 51, -1e18);
	for(int i = 1; i <= n; i ++) G[i][i][0] = 0;
	for(int i = 1; i <= m; i ++) {
		int u, v;
		scanf("%d%d", &u, &v);
		G[u][v][0] = p * w[v];
	}
	db t = p;
	for(int i = 1; i <= 50; i ++, t *= t) {
		for(int u = 1; u <= n; u ++) {
			for(int v = 1; v <= n; v ++) {
				for(int k = 1; k <= n; k ++) if(G[u][k][i - 1] >= 0 && G[k][v][i - 1] >= 0) {
					G[u][v][i] = max(G[u][v][i], G[u][k][i - 1] + t * G[k][v][i - 1]);
				}
			}
		}
	}
	db ans = 0;
	for(int i = 1; i <= n; i ++)
		ans = max(ans, G[s][i][50]);
	printf("%.1f\n", w[s] + ans);
	return 0;
}