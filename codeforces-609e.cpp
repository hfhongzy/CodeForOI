#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
struct Edge {
	int u, v, w, id;
	bool operator < (const Edge &e) const {
		return w < e.w;
	}
} e[N];
int n, m, idx, f[N];
bool tag[N];
int find(int u) { return u == f[u] ? u : f[u] = find(f[u]); }
bool unite(int u, int v) {
	u = find(u); v = find(v); f[u] = v;
	return u != v;
}
struct Edge2 { int v, w; };
vector<Edge2> G[N];
ll kruskal() {
	sort(e + 1, e + m + 1);
	for(int i = 1; i <= n; i ++) f[i] = i;
	int cnt = 0; ll ans = 0;
	for(int i = 1; i <= m; i ++) if(unite(e[i].u, e[i].v)) {
		G[e[i].u].push_back({e[i].v, e[i].w});
		G[e[i].v].push_back({e[i].u, e[i].w});
		cnt ++; tag[e[i].id] = 1; ans += e[i].w;
		if(cnt == n - 1) break ;
	}
	return ans;
}
int fa[N], top[N], d[N], son[N], sz[N], dfn[N], w[N];
void dfs1(int u) {
	sz[u] = 1; d[u] = d[fa[u]] + 1;
	for(auto e : G[u]) if(e.v != fa[u]) {
		w[e.v] = e.w; fa[e.v] = u; dfs1(e.v); sz[u] += sz[e.v];
		if(sz[e.v] > sz[son[u]]) son[u] = e.v;
	}
}
void dfs2(int u, int t) {
	top[u] = t; dfn[u] = ++ idx;
	if(son[u]) {
		dfs2(son[u], t);
		for(auto e : G[u]) if(!dfn[e.v]) dfs2(e.v, e.v);
	}
}
int st[N][20], lg[N];
void buildst() {
	lg[1] = 0;
	for(int i = 2; i <= n; i ++) lg[i] = lg[i >> 1] + 1;
	for(int i = 1; i <= n; i ++) st[dfn[i]][0] = w[i];
	for(int j = 1; j <= lg[n]; j ++) {
		for(int i = 1; i + (1 << j) - 1 <= n; i ++) {
			st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
		}
	} 
}
int queryst(int l, int r) {
	int k = lg[r - l + 1];
	return max(st[l][k], st[r - (1 << k) + 1][k]);
}
int qmax(int u, int v) {
	int ans = 0;
	while(top[u] ^ top[v]) {
		if(d[top[u]] < d[top[v]]) swap(u, v);
		ans = max(ans, queryst(dfn[top[u]], dfn[u]));
		u = fa[top[u]];
	}
	if(dfn[u] > dfn[v]) swap(u, v);
	if(dfn[u] ^ dfn[v]) {
		ans = max(ans, queryst(dfn[u] + 1, dfn[v]));
	}
	return ans;
}
int main() {
	freopen("input", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i ++) {
		scanf("%d%d%d", &e[i].v, &e[i].u, &e[i].w); e[i].id = i;
	}
	static ll res = kruskal(), ans[N];
	dfs1(1); dfs2(1, 1); buildst();
	for(int i = 1; i <= m; i ++) {
		if(tag[e[i].id]) ans[e[i].id] = res;
		else ans[e[i].id] = res - qmax(e[i].u, e[i].v) + e[i].w;
	}
	for(int i = 1; i <= m; i ++)
		printf("%lld\n", ans[i]);
	return 0;
}