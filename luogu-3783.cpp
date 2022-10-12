#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
#define pb push_back
using namespace std;
const int N = 2e5 + 50, M = N / 4, INF = 2e9 + 10;
struct FinalGraph {

struct Edge { int v, w; };
vector<Edge> G[N];
struct Node {
	int u, d;
	bool operator < (const Node &b) const { return d > b.d; }
};
int d[N], n;
void clr(int _n) {
	n = _n;
	for(int i = 1; i <= n; i ++) G[i].clear();
}
void link(int u, int v, int w) { G[u].pb((Edge) {v, w}); }
void Dijkstra() {
	fill(d + 1, d + n, INF);
	priority_queue<Node> pq; pq.push((Node) {n, d[n] = 0});
	while(pq.size()) {
		int u = pq.top().u, du = pq.top().d; pq.pop();
		// printf("extended %d\n", u);
		if(d[u] < du) continue ;
		for(int i = 0; i < (int) G[u].size(); i ++) {
			Edge &e = G[u][i];
			if(d[e.v] > d[u] + e.w) {
				pq.push((Node) {e.v, d[e.v] = d[u] + e.w});
			}
		}
	}
}

} gp;
vector<int> T[M];
int n, m, k, lgk, d[M], f[M][20], dfn[M], idx;
int ID(int d, int u) { return (d - 1) * m + u; }
int lca(int u, int v) {
	if(d[u] < d[v]) swap(u, v);
	int c = d[u] - d[v];
	for(int i = lgk - 1; ~ i; i --)
		if(c >> i & 1) u = f[u][i];
	if(u == v) return u;
	for(int i = lgk - 1; ~ i; i --)
		if(f[u][i] ^ f[v][i]) {
			u = f[u][i]; v = f[v][i];
		}
	return f[u][0];
}
void dfs(int u) {
	dfn[u] = ++ idx;
	for(int i = 1; i < lgk; i ++)
		f[u][i] = f[f[u][i - 1]][i - 1];
	for(int i = 0; i < (int) T[u].size(); i ++) {
		int v = T[u][i]; f[v][0] = u; d[v] = d[u] + 1; dfs(v);
	}
}
struct Edge {
	int id, uu;
	bool operator < (const Edge &e) const { return dfn[uu] < dfn[e.uu]; }
};
vector<Edge> G[M], rG[M];
int main() {
	// freopen("input", "r", stdin); freopen("out", "w", stdout);
	int test; scanf("%d", &test);
	while(test --) {
		scanf("%d%d%d", &n, &m, &k);
		for(int i = 1; i <= n; i ++) { G[i].clear(); rG[i].clear(); }
		for(int i = 1; i <= k; i ++) T[i].clear();
		for(lgk = 1; (1 << lgk) <= k; lgk ++) ;
		idx = 0; gp.clr(ID(4, m) + 1);
		for(int i = 1; i <= m; i ++) {
			int u, v, w, uu;
			scanf("%d%d%d%d", &u, &v, &w, &uu);
			G[u].pb((Edge) {i, uu});
			rG[v].pb((Edge) {i, uu});
			gp.link(ID(3, i), ID(1, i), w);
			gp.link(ID(4, i), ID(1, i), w);
			gp.link(ID(3, i), ID(2, i), w);
			gp.link(ID(4, i), ID(2, i), w);
		}
		for(int i = 0; i < (int) G[1].size(); i ++) {
			gp.link(gp.n, ID(3, G[1][i].id), 0);
			gp.link(gp.n, ID(4, G[1][i].id), 0);
		}
		for(int i = 1; i < k; i ++) {
			int u, v;
			scanf("%d%d%*d", &u, &v);
			T[u].pb(v);
		}
		f[1][0] = d[1] = 0; dfs(1); vector<Edge> tmp;
		for(int i = 1; i <= n; i ++) if(rG[i].size() && G[i].size()) {
			sort(rG[i].begin(), rG[i].end());
			sort(G[i].begin(), G[i].end());
			tmp.clear();
			for(int j = 0; j < (int) rG[i].size(); j ++) {
				tmp.pb(rG[i][j]);
				if(j) {
					gp.link(ID(1, rG[i][j - 1].id), ID(1, rG[i][j].id), 0);
					gp.link(ID(2, rG[i][j].id), ID(2, rG[i][j - 1].id), 0);
				}
			}
			for(int j = 0; j < (int) G[i].size(); j ++) {
				tmp.pb(G[i][j]);
				if(j) {
					gp.link(ID(3, G[i][j - 1].id), ID(3, G[i][j].id), 0);
					gp.link(ID(4, G[i][j].id), ID(4, G[i][j - 1].id), 0);
				}
			}
			sort(tmp.begin(), tmp.end());
			for(int j = 1; j < (int) tmp.size(); j ++) {
				int c = d[lca(tmp[j - 1].uu, tmp[j].uu)];
				vector<Edge>::iterator it1 = upper_bound(rG[i].begin(), rG[i].end(), tmp[j - 1]);
				vector<Edge>::iterator it2 = lower_bound(G[i].begin(), G[i].end(), tmp[j]);
				if(it1 != rG[i].begin() && it2 != G[i].end()) {
					it1 --;
					gp.link(ID(1, it1 -> id), ID(3, it2 -> id), c);
				}
				it1 = upper_bound(G[i].begin(), G[i].end(), tmp[j - 1]);
				it2 = lower_bound(rG[i].begin(), rG[i].end(), tmp[j]);
				if(it1 != G[i].begin() && it2 != rG[i].end()) {
					it1 --;
					gp.link(ID(2, it2 -> id), ID(4, it1 -> id), c);
				}
			}
		}
		gp.Dijkstra();
		for(int i = 2; i <= n; i ++) {
			int ans = INF;
			for(int j = 0; j < (int) rG[i].size(); j ++) {
				ans = min(ans, gp.d[ID(1, rG[i][j].id)]);
				ans = min(ans, gp.d[ID(2, rG[i][j].id)]);
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}