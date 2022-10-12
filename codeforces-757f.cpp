#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= (int) k; i ++)
typedef long long ll;
using namespace std;
template<class T> void chkmin(T &x, const T &y) { if(x > y) x = y; }
template<class T> void chkmax(T &x, const T &y) { if(x < y) x = y; }
const ll INF = 1e17 + 10;
const int N = 2e5 + 10;
int n, m, s, lgn, f[N][20];
struct Edge { int v, w; };
vector<Edge> G[N];
struct Node {
	int u; ll d;
	bool operator < (const Node &b) const { return d > b.d; }
};
ll d[N];
void Dijkstra(int s) {
	fill(d + 1, d + n + 1, INF);
	priority_queue<Node> pq; pq.push((Node) {s, d[s] = 0});
	while(pq.size()) {
		int u = pq.top().u; ll du = pq.top().d; pq.pop();
		if(d[u] < du) continue ;
		rep(i, 0, G[u].size() - 1) {
			Edge &e = G[u][i];
			if(d[e.v] > d[u] + e.w) {
				pq.push((Node) {e.v, d[e.v] = d[u] + e.w});
			}
		}
	}
}
void link(int u, int fa) {
	f[u][0] = fa; d[u] = d[fa] + 1;
	rep(i, 1, lgn - 1) f[u][i] = f[f[u][i - 1]][i - 1];
}
int lca(int u, int v) {
	if(!u || !v) return u | v;
	if(d[u] < d[v]) swap(u, v);
	int c = d[u] - d[v];
	for(int i = lgn - 1; i >= 0; i --)
		if(c >> i & 1) u = f[u][i];
	if(u == v) return u;
	for(int i = lgn - 1; i >= 0; i --)
		if(f[u][i] ^ f[v][i]) {
			u = f[u][i]; v = f[v][i];
		}
	return f[u][0];
}
struct Dominator {
	vector<int> G[N], fG[N], D[N];
	int ind[N], ans, sz[N];
	void add(int u, int p) {
		G[p].pb(u); fG[u].pb(p); ind[u] ++;
	}
	void dfs(int u) {
		sz[u] = 1;
		for(int v : D[u]) {
			dfs(v); sz[u] += sz[v];
		}
		if(u != s) ans = max(ans, sz[u]);
	}
	void build() {
		queue<int> q; q.push(s);
		while(q.size()) {
			int u = q.front(), p = 0; q.pop();
			for(int v : fG[u]) p = lca(p, v);
			if(p) link(u, p);
			for(int v : G[u]) if(!-- ind[v]) q.push(v);
		}
		rep(i, 1, n) if(f[i][0]) D[f[i][0]].pb(i);
		dfs(s);
	}
} T;
int main() {
	scanf("%d%d%d", &n, &m, &s);
	for(lgn = 1; (1 << lgn) <= n; lgn ++) ;
	rep(i, 1, m) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		G[u].pb({v, w}); G[v].pb({u, w});
	}
	Dijkstra(s);
	rep(i, 1, n) if(d[i] != INF) {
		for(auto e : G[i]) if(d[e.v] + e.w == d[i]) {
			T.add(i, e.v);
		}
	}
	T.build();
	printf("%d\n", T.ans);
	return 0;
}