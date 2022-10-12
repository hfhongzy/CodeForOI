#include <algorithm>
#include <vector>
#include <cstdio>
#include <queue>
using namespace std;
const int N = 510, M = 4e5 + 10, INF = 2e9 + 10;
namespace net {

const int N = 510, M = 4e5 + 10;
struct Edge {
	int v, c, f, nxt;
} e[M];
int ec, hd[N], n;
void init(int _n) {
	n = _n; fill(hd + 1, hd + n + 1, -1); ec = 0;
}
void add(int u, int v, int c) {
	e[ec] = (Edge) {v, c, 0, hd[u]}; hd[u] = ec ++;
	e[ec] = (Edge) {u, 0, 0, hd[v]}; hd[v] = ec ++;
}
int dis[N], cur[N];
bool bfs() {
	fill(dis + 1, dis + n + 1, -1);
	queue<int> q; q.push(1); dis[1] = 0;
	while(q.size()) {
		int u = q.front(); q.pop();
		for(int i = hd[u]; ~ i; i = e[i].nxt) {
			int v = e[i].v;
			if(e[i].f < e[i].c && -1 == dis[v]) {
				dis[v] = dis[u] + 1; q.push(v);
			}
		}
	}
	return ~ dis[n];
}
int dfs(int u, int a) {
	if(u == n || a == 0) return a;
	int ans = 0, f;
	for(int &i = cur[u]; ~ i; i = e[i].nxt) {
		int v = e[i].v;
		if(dis[v] == dis[u] + 1 && (f = dfs(v, min(a, e[i].c - e[i].f))) > 0) {
			ans += f; e[i].f += f; e[i ^ 1].f -= f;
			if((a -= f) == 0) break ;
		}
	}
	return ans;
}
int dinic() {
	int ans = 0;
	while(bfs()) {
		copy(hd + 1, hd + n + 1, cur + 1);
		ans += dfs(1, INF);
	}
	return ans;
}

}
namespace G {

const int M = N;
struct Edge { int v, w; };
vector<Edge> G[M];
struct Node {
	int u, d;
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
void Dijkstra(int s, int *d) {
	fill(d + 1, d + n + 1, INF);
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
}

}
struct Edge {
	int u, v, w, c;
} e[M];
int n, m, ds[N], dt[N];
int main() {
	scanf("%d%d", &n, &m);
	G::init(n);
	for(int i = 1; i <= m; i ++) {
		scanf("%d%d%d%d", &e[i].u, &e[i].v, &e[i].w, &e[i].c);
		G::link(e[i].u, e[i].v, e[i].w);
		G::link(e[i].v, e[i].u, e[i].w);
	}
	G::Dijkstra(1, ds); G::Dijkstra(1, dt);
	printf("%d\n", ds[n]);

	net::init(n);
	for(int i = 1; i <= m; i ++) {
		if(ds[e[i].u] + e[i].w == dt[e[i].v]) {
			net::add(e[i].u, e[i].v, e[i].c);
		} else if(ds[e[i].v] + e[i].w == dt[e[i].u]) {
			net::add(e[i].v, e[i].u, e[i].c);
		}
	}
	printf("%d\n", net::dinic());
	return 0;
}