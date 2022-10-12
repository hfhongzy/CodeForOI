#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
const ll INF = 2e18;
const int N = 3e5 + 10;
struct Edge { int v, id; ll w; };
vector<Edge> G[N];
struct Node {
	int u; ll d;
	bool operator < (const Node &b) const { return d > b.d; }
};
int n, m, k, fa[N], fw[N];
ll d[N];
void Dijkstra(int s) {
	fill(d + 1, d + n + 1, INF);
	priority_queue<Node> pq; pq.push((Node) {s, d[s] = 0});
	while(pq.size()) {
		int u = pq.top().u; ll du = pq.top().d; pq.pop();
		if(d[u] < du) continue ;
		for(int i = 0; i < (int) G[u].size(); i ++) {
			Edge &e = G[u][i];
			if(d[e.v] > d[u] + e.w) {
				fa[e.v] = u; fw[e.v] = e.id;
				d[e.v] = d[u] + e.w;
				pq.push((Node) {e.v, d[e.v]});
			}
		}
	}
}
vector<int> son[N], ans;
void dfs(int u) {
	if(ans.size() == k) return ;
	if(u != 1) ans.push_back(fw[u]);
	for(int v : son[u]) dfs(v);
}
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= m; i ++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		G[u].push_back({v, i, w});
		G[v].push_back({u, i, w});
	}
	Dijkstra(1);
	for(int i = 2; i <= n; i ++) son[fa[i]].push_back(i);
	dfs(1);
	printf("%d\n", (int) ans.size());
	for(int v : ans) printf("%d ", v);
	return 0;
}