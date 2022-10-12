#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
const int N = 3e5 + 10, mod = 998244353;
int n, m, d[N], f[N][20], w[N][51], s[N][51];
vector<int> G[N];
void dfs(int u, int fa = 0) {
	f[u][0] = fa; d[u] = fa ? d[fa] + 1 : 0; w[u][0] = 1;
	for(int i = 1; i <= 50; i ++) w[u][i] = 1ll * w[u][i - 1] * d[u] % mod;
	for(int i = 1; i <= 50; i ++) {
		s[u][i] = (s[fa][i] + w[u][i]) % mod;
	}
	for(int i = 1; i < 20; i ++) f[u][i] = f[f[u][i - 1]][i - 1];
	for(int i = 0; i < (int) G[u].size(); i ++) {
		int v = G[u][i];
		if(v != fa) dfs(v, u);
	}
}
int lca(int u, int v) {
	if(d[u] < d[v]) swap(u, v);
	int c = d[u] - d[v];
	for(int i = 19; i >= 0; i --)
		if(c >> i & 1) u = f[u][i];
	if(u == v) return u;
	for(int i = 19; i >= 0; i --)
		if(f[u][i] != f[v][i]) {
			u = f[u][i]; v = f[v][i];
		}
	return f[u][0];
}
int main() {
	scanf("%d", &n);
	for(int i = 1, u, v; i < n; i ++) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1);
	scanf("%d", &m);
	for(int u, v, k, i = 1; i <= m; i ++) {
		scanf("%d%d%d", &u, &v, &k); int x = lca(u, v);
		printf("%d\n", (((long long) s[u][k] + s[v][k] - 2ll * s[x][k] + w[x][k]) % mod + mod) % mod);
	}
	return 0;
}