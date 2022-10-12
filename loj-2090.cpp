#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
#define pback push_back
#define rep(i, j, k) for(int i = j; i <= (int) k; i ++)
#define id(i, j) ((i - 1) * m + j)
using namespace std;
template<class T> void chkmin(T &x, const T &y) { if(x > y) x = y; }
template<class T> void chkmax(T &x, const T &y) { if(x < y) x = y; }
const int N = 2e4 + 10, M = 1e5 + 10, INF = 2e9 + 10;
int n, m, q, ans[M];
struct Query {
	int u, v, id;
	int col(int x) {
		int t1 = (u - 1) % m + 1, t2 = (v - 1) % m + 1;
		return max(t1, t2) < x ? -1 : min(t1, t2) > x;
	}
} a[M];
struct Edge { int v, w; };
vector<Edge> G[N];
struct Node {
	int u, d;
	bool operator < (const Node &b) const { return d > b.d; }
};
int d[N];
bool ban[N];
void Dijkstra(int s) {
	priority_queue<Node> pq; pq.push((Node) {s, d[s] = 0});
	while(pq.size()) {
		int u = pq.top().u, du = pq.top().d; pq.pop();
		if(d[u] < du) continue ;
		rep(i, 0, G[u].size() - 1) {
			Edge &e = G[u][i];
			if(!ban[e.v] && d[e.v] > d[u] + e.w) {
				pq.push((Node) {e.v, d[e.v] = d[u] + e.w});
			}
		}
	}
}
void solve(int ql, int qr, int xl, int yl, int xr, int yr) {
	if(xl > xr || yl > yr || ql > qr) return ;
	static Query tmp[M];
	int pl = ql, pr = qr;
	if(xr - xl > yr - yl) {
		int xm = (xl + xr) >> 1;
		rep(y, yl, yr) {
			rep(i, xl, xr) rep(j, yl, yr) d[id(i, j)] = INF;
			Dijkstra(id(xm, y));
			rep(i, ql, qr) chkmin(ans[a[i].id], d[a[i].u] + d[a[i].v]);
		}
		rep(i, ql, qr) {
			if(a[i].v < id(xm, yl)) tmp[pl ++] = a[i];
			else if(a[i].u > id(xm, yr)) tmp[pr --] = a[i];
		}
		if(ql != pl) copy(tmp + ql, tmp + pl, a + ql);
		if(qr != pr) copy(tmp + pr + 1, tmp + qr + 1, a + pr + 1);
		rep(y, yl, yr) ban[id(xm, y)] = 1;
		solve(ql, pl - 1, xl, yl, xm - 1, yr);
		solve(pr + 1, qr, xm + 1, yl, xr, yr);
	} else {
		int ym = (yl + yr) >> 1;
		rep(x, xl, xr) {
			rep(i, xl, xr) rep(j, yl, yr) d[id(i, j)] = INF;
			Dijkstra(id(x, ym));
			rep(i, ql, qr) chkmin(ans[a[i].id], d[a[i].u] + d[a[i].v]);
		}
		rep(i, ql, qr) {
			if(a[i].col(ym) == -1) tmp[pl ++] = a[i];
			else if(a[i].col(ym) == 1) tmp[pr --] = a[i];
		}
		if(ql != pl) copy(tmp + ql, tmp + pl, a + ql);
		if(qr != pr) copy(tmp + pr + 1, tmp + qr + 1, a + pr + 1);
		rep(x, xl, xr) ban[id(x, ym)] = 1;
		solve(ql, pl - 1, xl, yl, xr, ym - 1);
		solve(pr + 1, qr, xl, ym + 1, xr, yr);
	}
}
int main() {
	scanf("%d%d", &n, &m);
	rep(i, 1, n) rep(j, 1, m - 1) {
		int w; scanf("%d", &w);
		G[id(i, j)].pback((Edge) {id(i, j + 1), w});
		G[id(i, j + 1)].pback((Edge) {id(i, j), w});
	}
	rep(i, 1, n - 1) rep(j, 1, m) {
		int w; scanf("%d", &w);
		G[id(i, j)].pback((Edge) {id(i + 1, j), w});
		G[id(i + 1, j)].pback((Edge) {id(i, j), w});
	}
	scanf("%d", &q);
	rep(i, 1, q) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		a[i].u = id(x1, y1); a[i].v = id(x2, y2); a[i].id = i;
		if(a[i].u > a[i].v) swap(a[i].u, a[i].v);
		ans[i] = a[i].u == a[i].v ? 0 : INF;
	}
	solve(1, q, 1, 1, n, m);
	rep(i, 1, q) printf("%d\n", ans[i]);
	return 0;
}