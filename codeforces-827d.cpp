#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 2e5 + 10, INF = 2e9 + 10;
struct Edge {
	int u, v, w, id;
	bool operator < (const Edge &b) const {
		return w < b.w;
	}
} e[N];
int n, m, lgn, f[N], g[N][20], h[N][20], ans[N], d[N], eid[N];
bool use[N];
int find(int u) { return u == f[u] ? u : f[u] = find(f[u]); }
bool unite(int u, int v) {
	u = find(u); v = find(v);
	return u == v ? 0 : (f[u] = v, 1);
}
struct Node {
	int v, w, id;
	Node() {}
	Node(int a, int b, int c) : v(a), w(b), id(c) {}
};
vector<Node> G[N];
void dfs(int u, int fa = 0) {
	g[u][0] = fa; d[u] = d[fa] + 1;
	for(int i = 1; i < lgn; i ++) {
		g[u][i] = g[g[u][i - 1]][i - 1];
		h[u][i] = max(h[u][i - 1], h[g[u][i - 1]][i - 1]);
	}
	for(int i = 0; i < (int) G[u].size(); i ++) {
		int v = G[u][i].v;
		if(v ^ fa) {
			h[v][0] = G[u][i].w;
			eid[v] = G[u][i].id;
			dfs(v, u);
		}
	}
}
pair<int, int> qmax(int u, int v) {
	if(d[u] < d[v]) swap(u, v);
	int c = d[u] - d[v], ans = 0;
	for(int i = lgn - 1; i >= 0; i --)
		if(c >> i & 1) {
			ans = max(ans, h[u][i]);
			u = g[u][i];
		}
	if(u == v) return pair<int, int>(u, ans);
	for(int i = lgn - 1; i >= 0; i --)
		if(g[u][i] ^ g[v][i]) {
			ans = max(ans, h[u][i]);
			ans = max(ans, h[v][i]);
			u = g[u][i]; v = g[v][i];
		}
	ans = max(ans, max(h[u][0], h[v][0]));
	return pair<int, int>(g[u][0], ans);
}
int tmp[N];
void solve(int u, int v, int w) {
	u = find(u);
	while(d[u] > d[v]) {
		tmp[u] = w;
		u = f[u] = find(g[u][0]);
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for(lgn = 1; (1 << lgn) <= n; lgn ++) ;
	for(int i = 1; i <= m; i ++) {
		scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
		e[i].id = i;
	}
	sort(e + 1, e + m + 1);
	for(int i = 1; i <= n; i ++) f[i] = i;
	for(int i = 1; i <= m; i ++) {
		int &u = e[i].u, &v = e[i].v, &w = e[i].w;
		if(unite(u, v)) {
			G[u].push_back(Node(v, w, e[i].id));
			G[v].push_back(Node(u, w, e[i].id));
			use[i] = 1;
		}
	}
	dfs(1);
	fill(tmp + 1, tmp + n + 1, INF);
	for(int i = 1; i <= n; i ++) f[i] = i;
	for(int i = 1; i <= m; i ++) if(!use[i]) {
		pair<int, int> t = qmax(e[i].u, e[i].v);
		ans[e[i].id] = t.second - 1;
		solve(e[i].u, t.first, e[i].w);
		solve(e[i].v, t.first, e[i].w);
	}
	for(int i = 2; i <= n; i ++) ans[eid[i]] = tmp[i] == INF ? -1 : tmp[i] - 1;
	for(int i = 1; i <= m; i ++)
		printf("%d%c", ans[i], " \n"[i == m]);
	return 0;
}
/*
on tree : 倍增覆盖取min呗
not on tree : max(链) - 1
*/