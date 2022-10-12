#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
const int N = 1520, M = 5050, INF = 2e9 + 10, mod = 1e9 + 7;
struct Edge { int v, w; };
vector<Edge> G[M];
struct Node {
	int u, d;
	bool operator < (const Node &b) const {
		return d > b.d;
	}
};
int n, m, d[N], f[N], g[N], uu[M], vv[M], ww[M], h[M];
int dp(int u) {
	if(g[u]) return g[u];
	g[u] = 1;
	for(int i = 0; i < (int) G[u].size(); i ++) {
		Edge &e = G[u][i];
		if(e.w + d[u] == d[e.v]) {
			(g[u] += dp(e.v)) %= mod;
		}
	}
	return g[u];
}
void Dijkstra(int s) {
	fill(d + 1, d + n + 1, INF);
	priority_queue<Node> pq;
	pq.push((Node) {s, d[s] = 0});
	fill(f + 1, f + n + 1, 0); f[s] = 1;
	while(pq.size()) {
		int u = pq.top().u, du = pq.top().d; pq.pop();
		if(d[u] < du) continue ;
		for(int i = 0; i < (int) G[u].size(); i ++) {
			Edge &e = G[u][i];
			if(d[e.v] > d[u] + e.w) {
				d[e.v] = d[u] + e.w; f[e.v] = f[u];
				pq.push((Node) {e.v, d[e.v]});
			} else if(d[e.v] == d[u] + e.w) {
				(f[e.v] += f[u]) %= mod;
			}
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i ++) {
		scanf("%d%d%d", uu + i, vv + i, ww + i);
		G[uu[i]].push_back((Edge) {vv[i], ww[i]});
	}
	for(int i = 1; i <= n; i ++) {
		Dijkstra(i);
		fill(g + 1, g + n + 1, 0); dp(i);
		for(int j = 1; j <= m; j ++) {
			if(d[uu[j]] + ww[j] == d[vv[j]]) {
				(h[j] += 1ll * f[uu[j]] * g[vv[j]] % mod) %= mod;
			}
		}
	}
	for(int i = 1; i <= m; i ++)
		printf("%d\n", h[i]);
	return 0;
}