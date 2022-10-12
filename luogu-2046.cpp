#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
#define rep(i, j, k) for(int i = j; i <= (int) k; i ++)
using namespace std;
const int N = 510, INF = 2e9 + 10;
int n, id, num[N][N];
namespace G {

const int M = N * N;
struct Edge { int v, w; };
vector<Edge> G[M];
struct Node {
	int u, d;
	bool operator < (const Node &b) const { return d > b.d; }
};
int n;
void link(int u, int v, int w) {
	G[u].push_back((Edge) {v, w});
}
int Dijkstra(int s, int t) {
	static int d[M]; fill(d + 1, d + n + 1, INF);
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
	return d[t];
}

}
int main() {
	scanf("%d", &n);
	int s = 1, t = id = 2;
	rep(i, 1, n) {
		num[0][i] = num[i][n + 1] = s;
		num[i][0] = num[n + 1][i] = t;
	}
	rep(i, 1, n) rep(j, 1, n) num[i][j] = ++ id;
	G::n = id;
	rep(i, 0, n) rep(j, 1, n) {
		int x; scanf("%d", &x);
		G::link(num[i][j], num[i + 1][j], x);
	}
	rep(i, 1, n) rep(j, 0, n) {
		int x; scanf("%d", &x);
		G::link(num[i][j + 1], num[i][j], x);
	}
	rep(i, 0, n) rep(j, 1, n) {
		int x; scanf("%d", &x);
		G::link(num[i + 1][j], num[i][j], x);
	}
	rep(i, 1, n) rep(j, 0, n) {
		int x; scanf("%d", &x);
		G::link(num[i][j], num[i][j + 1], x);
	}
	printf("%d\n", G::Dijkstra(s, t));
	return 0;
}