#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
#define pback push_back
#define rep(i, j, k) for(int i = j; i <= (int) k; i ++)
#define id(i, j) ((i - 1) * m + j)
typedef long long ll;
using namespace std;
template<class T> void chkmin(T &x, const T &y) { if(x > y) x = y; }
template<class T> void chkmax(T &x, const T &y) { if(x < y) x = y; }

const int N = 1e5 + 10;
int n, m, s, t;
bool cut[N];
struct tuple {
	int u, v, w;
} a[N];

struct Graph {

ll d[N];
struct Edge { int v, w, id; };
vector<Edge> G[N];
struct Node {
	int u; ll d;
	bool operator < (const Node &b) const { return d > b.d; }
};
void Dijkstra(int s) {
	static const ll INF = 1e14 + 5;
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
int dfn[N], low[N], idx, f[N], fd[N];
void tarjan(int u, int fa = 0, int ed = 0) {
	dfn[u] = low[u] = ++ idx; f[u] = fa; fd[u] = ed;
	for(auto e : G[u]) {
		if(!dfn[e.v]) {
			tarjan(e.v, u, e.id);
			low[u] = min(low[u], low[e.v]);
			if(low[e.v] > dfn[u]) {
				cut[e.id] = 1;
			}
		} else if(e.v != fa) {
			if(f[e.v] == u) {
				cut[fd[e.v]] = 0;
			}
			low[u] = min(low[u], dfn[e.v]);
		}
	}
}

} G1, G2, G3;
int main() {
	scanf("%d%d%d%d", &n, &m, &s, &t);
	rep(i, 1, m) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		G1.G[u].pback({v, w, i});
		G2.G[v].pback({u, w, i});
		a[i] = {u, v, w};
	}
	G1.Dijkstra(s); G2.Dijkstra(t);
	ll dis = G1.d[t];
	rep(u, 1, n) {
		for(auto e : G1.G[u]) if(G1.d[u] + G2.d[e.v] + e.w == dis) {
			G3.G[u].pback({e.v, e.w, e.id});
			G3.G[e.v].pback({u, e.w, e.id});
		}
	}
	rep(i, 1, n) if(!G3.dfn[i]) G3.tarjan(i);
	rep(i, 1, m) {
		if(cut[i]) puts("YES");
		else {
			if(G1.d[a[i].u] + G2.d[a[i].v] + 1 < dis) {
				printf("CAN %lld\n", G1.d[a[i].u] + G2.d[a[i].v] + a[i].w - (dis - 1));
			} else {
				puts("NO");
			}
		}
	}
	return 0;
}
/*
最短路上边建出来，桥是YES。否则若ds[u] + dt[v] + 1 < dis就CAN。
*/