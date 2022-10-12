#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 5005, mod = 1e9 + 7;
int n, g[N], f[N][N], sz[N], t[N];
vector<int> G[N];
void dfs(int u, int fa = 0) {
	sz[u] = f[u][1] = 1;
	for(int i = 0; i < (int) G[u].size(); i ++) {
		int v = G[u][i];
		if(v == fa) continue ;
		dfs(v, u);
		fill(t, t + sz[u] + sz[v] + 1, 0);
		for(int j = sz[u]; j >= 1; j --) {
			for(int k = sz[v]; k >= 1; k --) {
				(t[j + k] += 1ll * f[u][j] * f[v][k] % mod) %= mod;
				(t[j] += 1ll * f[u][j] * f[v][k] % mod * (mod - g[k]) % mod) %= mod;
			}
		}
		sz[u] += sz[v];
		copy(t, t + sz[u] + 1, f[u]);
	}
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i ++) {
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	g[0] = 1;
	for(int i = 2; i <= n; i += 2)
		g[i] = g[i - 2] * (i - 1ll) % mod;
	dfs(1);
	int ans = 0;
	for(int i = 2; i <= n; i += 2)
		(ans += 1ll * f[1][i] * g[i] % mod) %= mod;
	printf("%d\n", ans);
	return 0;
}