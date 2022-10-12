#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
typedef unsigned long long ull;
const int N = 17;
int n, m, G[N], tpo[N], T[N], fa[N];
ull dp[N][N];
void bfs(int s) {
	static bool vis[N];
	queue<int> q; q.push(s); fa[s] = -1; vis[s] = 1;
	int le = 0;
	while(q.size()) {
		int u = q.front(); q.pop(); tpo[le ++] = u;
		for(int e = T[u]; e; e &= e - 1) {
			int v = __builtin_ctz(e);
			if(!vis[v]) {
				vis[v] = 1; fa[v] = u; q.push(v);
			}
		}
	}
}
ull calc(int S) {
	for(int i = n - 1; ~ i; i --) {
		int u = tpo[i];
		for(int j = 0; j < n; j ++) dp[u][j] = S >> j & 1;
		for(int e = T[u]; e; e &= e - 1) {
			int v = __builtin_ctz(e);
			if(v != fa[u]) {
				for(int x = S; x; x &= x - 1) {
					int c = __builtin_ctz(x);
					ull cur = 0;
					for(int y = G[c] & S; y; y &= y - 1) {
						int c2 = __builtin_ctz(y);
						cur += dp[v][c2];
					}
					dp[u][c] *= cur;
				}
			}
		}
	}
	ull ans = 0;
	for(int i = 0; i < n; i ++)
		ans += dp[0][i];
	return ans;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i ++) {
		int u, v;
		scanf("%d%d", &u, &v); u --; v --;
		G[u] |= 1 << v; G[v] |= 1 << u;
	}
	for(int i = 0; i < n - 1; i ++) {
		int u, v;
		scanf("%d%d", &u, &v); u --; v --;
		T[u] |= 1 << v; T[v] |= 1 << u;
	}
	bfs(0);
	ull res = 0;
	for(int i = 1; i < (1 << n); i ++) {
		int c = __builtin_popcount(i);
		res += ((n - c) & 1 ? -1 : 1) * calc(i);
	}
	printf("%llu\n", res);
	return 0;
}