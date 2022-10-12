#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 5e5 + 10, INF = 2e9 + 10;
int n, lgn, k, m;
struct Ufs {
	int f[N];
	void init(int n) {
		for(int i = 1; i <= n; i ++)
			f[i] = i;
	}
	int find(int u) {
		return u == f[u] ? u : f[u] = find(f[u]);
	}
	bool unite(int u, int v) {
		u = find(u); v = find(v);
		return u == v ? 0 : (f[u] = v, 1);
	}
} ufs;
struct Edge {
	int v, ty;
};
vector<Edge> G[N];
struct Node {
	int u, v, w;
	bool operator < (const Node &b) const {
		return w < b.w;
	}
} e[N];
int ty[N], d[N], f[N][20], val[N];
void dfs(int u, int fa = 0) {
	d[u] = d[fa] + 1; f[u][0] = fa;
	for(int i = 1; i < lgn; i ++)
		f[u][i] = f[f[u][i - 1]][i - 1];
	for(Edge &e : G[u]) if(e.v ^ fa) {
		ty[e.v] = e.ty; dfs(e.v, u);
	}
}
int lca(int u, int v) {
	if(d[u] < d[v]) swap(u, v);
	int c = d[u] - d[v], ans = 0;
	for(int i = lgn - 1; i >= 0; i --)
		if(c >> i & 1) u = f[u][i];
	if(u == v) return u;
	for(int i = lgn - 1; i >= 0; i --)
		if(f[u][i] ^ f[v][i]) {
			u = f[u][i]; v = f[v][i];
		}
	return f[u][0];
}
void solve(int u, int v, int w) {
	u = ufs.find(u);
	while(d[u] > d[v]) {
		val[u] = w;
		u = ufs.f[u] = ufs.find(f[u][0]);
	}
}
int main() {
	scanf("%d%d%d", &n, &k, &m);
	for(lgn = 1; (1 << lgn) <= n; lgn ++) ;
	ufs.init(n);
	for(int i = 1; i <= k; i ++) {
		int u, v;
		scanf("%d%d", &u, &v);
		ufs.unite(u, v);
		G[u].push_back({v, 1});
		G[v].push_back({u, 1});
	}
	for(int i = 1; i <= m; i ++) {
		scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
	}
	sort(e + 1, e + m + 1);
	static bool use[N];
	for(int i = 1; i <= m; i ++) {
		int &u = e[i].u, &v = e[i].v;
		if(ufs.unite(u, v)) {
			G[u].push_back({v, 0});
			G[v].push_back({u, 0});
			use[i] = 1;
		}
	}
	dfs(1); ufs.init(n);
	fill(val + 1, val + n + 1, INF);
	for(int i = 1; i <= m; i ++) if(!use[i]) {
		int &u = e[i].u, &v = e[i].v, &w = e[i].w;
		int l = lca(u, v);
		solve(u, l, w); solve(v, l, w);
	}
	long long ans = 0;
	for(int i = 1; i <= n; i ++) if(ty[i]) {
		if(val[i] == INF) return puts("-1"), 0;
		else ans += val[i];
	}
	printf("%lld\n", ans);
	return 0;
}