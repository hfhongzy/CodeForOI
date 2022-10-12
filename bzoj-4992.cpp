#include <algorithm>
#include <vector>
#include <cstdio>
#include <queue>
using namespace std;
typedef long long ll;
const int N = 110, M = N * N * 3 + 10;
const ll INF = 1e18;
int n, t, a[N][N];
int id(int x, int y, int z) {
	return (x - 1) * n + y + (z - 1) * n * n;
}
namespace G {

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
ll d[M];
void Dijkstra(int s) {
	fill(d + 1, d + n + 1, INF);
	priority_queue<Node> pq; pq.push((Node) {s, d[s] = 0});
	while(pq.size()) {
		int u = pq.top().u; ll du = pq.top().d; pq.pop();
		if(d[u] < du) continue ;
		for(int i = 0; i < (int) G[u].size(); i ++) {
			Edge &e = G[u][i];
			if(d[e.v] > d[u] + e.w) {
				d[e.v] = d[u] + e.w; pq.push((Node) {e.v, d[e.v]});
			}
		}
	}
}

}
int main() {
	scanf("%d%d", &n, &t);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			scanf("%d", &a[i][j]);
	G::init(n * n * 3);
	const int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= n; j ++) {
			for(int k = 0; k < 4; k ++) {
				int x = i + dx[k], y = j + dy[k];
				if(min(x, y) < 1 || max(x, y) > n) continue ;
				G::link(id(i, j, 1), id(x, y, 2), t);
				G::link(id(i, j, 2), id(x, y, 3), t);
				G::link(id(i, j, 3), id(x, y, 1), t + a[x][y]);
			}
		}
	}
	G::Dijkstra(id(1, 1, 1));
	printf("%lld\n", min(G::d[id(n, n, 1)], min(G::d[id(n, n, 2)], G::d[id(n, n, 3)])));
	return 0;
}