#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
const ll INF = 2e18;
namespace _G {

const int M = N * 4;
struct Edge { int v, w; };
vector<Edge> G[M];
struct Node {
	int u; ll d;
	bool operator < (const Node &b) const {
		return d > b.d;
	}
};
int n;
void init(int _n) {
	n = _n;
}
void link(int u, int v, int w) {
	G[u].push_back((Edge) {v, w});
}
ll Dijkstra(int s) {
	static ll d[M]; fill(d + 1, d + n + 1, INF);
	priority_queue<Node> pq; pq.push((Node) {s, d[s] = 0});
	while(pq.size()) {
		int u = pq.top().u, du = pq.top().d; pq.pop();
		if(d[u] < du) continue ;
		for(int i = 0; i < (int) G[u].size(); i ++) {
			Edge &e = G[u][i];
			if(d[e.v] > d[u] + e.w) {
				d[e.v] = d[u] + e.w; pq.push((Node) {e.v, d[e.v]});
			}
		}
	}
	return d[n];
}

}
int n, m;
struct Edge { int out, in, w; };
vector<Edge> G[N];
bool cmp(Edge a, Edge b) { return a.w < b.w; }
int main() {
	scanf("%d%d", &n, &m); _G::init(2 * m + 2);
	for(int i = 1; i <= m; i ++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		G[u].push_back((Edge) {i, i + m, w});
		G[v].push_back((Edge) {i + m, i, w});
		if(u == 1) _G::link(2 * m + 1, i, w);
		if(v == 1) _G::link(2 * m + 1, i + m, w);
		if(v == n) _G::link(i, 2 * m + 2, w);
		if(u == n) _G::link(i + m, 2 * m + 2, w);
	}
	for(int u = 1; u <= n; u ++) {
		sort(G[u].begin(), G[u].end(), cmp);
		for(int i = 0; i < (int) G[u].size(); i ++) {
			Edge &e = G[u][i];
			_G::link(e.in, e.out, e.w);
			if(i) {
				_G::link(G[u][i - 1].out, e.out, e.w - G[u][i - 1].w);
				_G::link(e.out, G[u][i - 1].out, 0);
			}
		}
	}
	printf("%lld\n", _G::Dijkstra(2 * m + 1));
	return 0;
}