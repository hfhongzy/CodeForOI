#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
typedef long double db;
const int N = 1005, INF = 2e9 + 10;
int n, m, a[N];
struct Edge { int v, w; db c; };
vector<Edge> G[N];
struct Node {
	int u, d;
	bool operator < (const Node &b) const { return d > b.d; }
};
int d[N], s;
bool vis[N];
db g[N], d2[N], ans[N];
void dp(int u) {
	if(vis[u]) return ;
	vis[u] = 1; g[u] = a[u] / d2[u];
	for(int i = 0; i < (int) G[u].size(); i ++) {
		Edge &e = G[u][i];
		if(e.w + d[u] == d[e.v]) {
			dp(e.v); g[u] += g[e.v] * e.c;
		}
	}
}
void Dijkstra() {
	fill(d + 1, d + n + 1, INF); fill(d2 + 1, d2 + n + 1, 0);
	priority_queue<Node> pq; pq.push((Node) {s, d[s] = 0}); d2[s] = 1;
	while(pq.size()) {
		int u = pq.top().u, du = pq.top().d; pq.pop();
		if(d[u] < du) continue ;
		for(int i = 0; i < (int) G[u].size(); i ++) {
			Edge &e = G[u][i];
			if(d[e.v] > d[u] + e.w) {
				d2[e.v] = d2[u] * e.c;
				d[e.v] = d[u] + e.w; pq.push((Node) {e.v, d[e.v]});
			} else if(d[e.v] == d[u] + e.w) {
				d2[e.v] += d2[u] * e.c;
			}
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++) scanf("%d", a + i);
	for(int i = 1; i <= m; i ++) {
		int u, v, w; db c;
		scanf("%d%d%d%Lf", &u, &v, &w, &c);
		G[u].push_back((Edge) {v, w, c});
		G[v].push_back((Edge) {u, w, c});
	}
	for(s = 1; s <= n; s ++) {
		Dijkstra();
		fill(vis + 1, vis + n + 1, 0); dp(s);
		for(int t = 1; t <= n; t ++) if(t != s && d[t] < INF) {
			g[t] -= a[t] / d2[t];
			ans[t] += d2[t] * g[t] * a[s];
		}
	}
	for(int i = 1; i <= n; i ++)
		printf("%.7Lf\n", ans[i]);
	return 0;
}