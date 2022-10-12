#include <algorithm>
#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 2e4 + 10;
int n, m, q, cnt, f[N][18], d[N];

struct Edge { int v; ll w; };
vector<Edge> G[N], T[N];

int dfn[N], idx, fa[N];
bool cir[N];
ll faw[N], sum[N], dis[N];
void solve(int u, int v, ll w) {
	cnt ++; int p = 0;
	for(int x = u; x != v; p = x, x = fa[x]) {
		cir[x] = 1; sum[x] = sum[p] + faw[p];
	}
	ll sv = sum[p] + faw[p];
	sum[cnt] = sv + w;
	for(int x = u; x != v; x = fa[x]) {
		ll y = min(sv - sum[x], sum[cnt] - sv + sum[x]);
		T[x].push_back((Edge) {cnt, y});
		T[cnt].push_back((Edge) {x, y});
	}
	T[v].push_back((Edge) {cnt, 0});
	T[cnt].push_back((Edge) {v, 0});
}
void dfs(int u) {
	dfn[u] = ++ idx;
	for(int i = 0; i < (int) G[u].size(); i ++) {
		int v = G[u][i].v; ll w = G[u][i].w;
		if(!dfn[v]) {
			fa[v] = u; faw[v] = w; dfs(v);
		} else if(dfn[u] > dfn[v] && v != fa[u]) {
			solve(u, v, w);
		}
	}
	if(fa[u] && !cir[u]) {
		T[u].push_back((Edge) {fa[u], faw[u]});
		T[fa[u]].push_back((Edge) {u, faw[u]});
	}
}
void dfs2(int u) {
	for(int i = 1; i <= 16; i ++)
		f[u][i] = f[f[u][i - 1]][i - 1];
	for(int i = 0; i < (int) T[u].size(); i ++) {
		int v = T[u][i].v; ll w = T[u][i].w;
		if(v != f[u][0]) {
			f[v][0] = u;
			dis[v] = dis[u] + w;
			d[v] = d[u] + 1;
			dfs2(v);
		}
	}
}
int lca(int u, int v) {
	if(d[u] < d[v]) swap(u, v);
	int c = d[u] - d[v];
	for(int i = 16; ~ i; i --)
		if(c >> i & 1) u = f[u][i];
	if(u == v) return u;
	for(int i = 16; ~ i; i --)
		if(f[u][i] ^ f[v][i]) {
			u = f[u][i]; v = f[v][i];
		}
	return f[u][0];
}
int kth(int u, int k) {
	for(int i = 16; ~ i; i --)
		if(k >> i & 1) u = f[u][i];
	return u;
}
int last(int u, int x) {
	return kth(u, d[u] - d[x] - 1);
}
int main() {
	scanf("%d%d%d", &n, &m, &q); cnt = n;
	for(int i = 1; i <= m; i ++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		G[u].push_back((Edge) {v, w});
		G[v].push_back((Edge) {u, w});
	}
	dfs(1); dfs2(1);
	for(int i = 1; i <= q; i ++) {
		int u, v;
		scanf("%d%d", &u, &v);
		int x = lca(u, v);
		if(x <= n) printf("%lld\n", dis[u] + dis[v] - 2 * dis[x]);
		else {
			int u0 = last(u, x), v0 = last(v, x);
			ll tmp = min(abs(sum[u0] - sum[v0]), sum[x] - abs(sum[u0] - sum[v0]));
			printf("%lld\n", dis[u] - dis[u0] + dis[v] - dis[v0] + tmp);
		}
	}
	return 0;
}