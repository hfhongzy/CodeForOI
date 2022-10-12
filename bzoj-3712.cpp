#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 2e5 + 10;

int n, m, k, idx, a[N], f[N][18], d[N], dfn[N];
bool isr[N];
vector<int> G[N];
void dfs(int u, int fa = 0) {
	d[u] = d[fa] + 1; f[u][0] = fa; dfn[u] = ++ idx;
	for(int i = 1; i < 18; i ++)
		f[u][i] = f[f[u][i - 1]][i - 1];
	for(int i = 0; i < (int) G[u].size(); i ++) {
		int v = G[u][i]; dfs(v, u);
	}
}
int lca(int u, int v) {
	if(d[u] < d[v]) swap(u, v);
	int c = d[u] - d[v];
	for(int i = 17; ~ i; i --)
		if(c >> i & 1) u = f[u][i];
	if(u == v) return u;
	for(int i = 17; ~ i; i --)
		if(f[u][i] ^ f[v][i]) {
			u = f[u][i]; v = f[v][i];
		}
	return f[u][0];
}
long long ans;
struct node {
	int fs, sc, pri;
	bool operator < (const node &b) const {
		if(max(dfn[fs], dfn[sc]) == max(dfn[b.fs], dfn[b.sc])) return pri < b.pri;
		return max(dfn[fs], dfn[sc]) < max(dfn[b.fs], dfn[b.sc]);
	}
};
vector<node> e[N];
void dfs2(int u, int fa = 0) {
	for(int i = 0; i < (int) G[u].size(); i ++) {
		dfs2(G[u][i], u);
	}
	sort(e[u].begin(), e[u].end());
	for(int i = 0; i < (int) e[u].size(); i ++) {
		node c = e[u][i];
		if(a[c.fs] && a[c.sc]) {
			int t = min(a[c.fs], a[c.sc]);
			ans += t * 2ll; a[c.fs] -= t; a[c.sc] -= t;
		}
	}
}
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; i ++) { scanf("%d", a + i); isr[i] = 1; }
	for(int u, v, i = 1; i <= m; i ++) {
		scanf("%d%d", &u, &v); isr[u] = 0;
		G[v].push_back(u);
	}
	for(int i = 1; i <= n; i ++) if(isr[i]) dfs(i);
	for(int u, v, i = 1; i <= k; i ++) {
		scanf("%d%d", &u, &v); int x = lca(u, v);
		if(x) e[x].push_back((node) {u, v, i});
	}
	for(int i = 1; i <= n; i ++) if(isr[i]) dfs2(i);
	printf("%lld\n", ans);
	return 0;
}