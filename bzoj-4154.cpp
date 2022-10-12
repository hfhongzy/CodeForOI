#include <algorithm>
#include <cctype>
#include <cstdio>
using namespace std;
const int N = 1e5 + 5;
const int mo = 1e9 + 7;
int n, m, q, p[N], x[N], y[N], dr[N];
int rt, cmpd, ls[N], rs[N], xl[N], xr[N], yl[N], yr[N], col[N], tag[N];
void upd(int u) {
	xl[u] = xr[u] = x[u]; yl[u] = yr[u] = y[u]; int t;
	if(t = ls[u]) {
		xl[u] = xl[u] < xl[t] ? xl[u] : xl[t];
		xr[u] = xr[u] > xr[t] ? xr[u] : xr[t];
		yl[u] = yl[u] < yl[t] ? yl[u] : yl[t];
		yr[u] = yr[u] > yr[t] ? yr[u] : yr[t];
	}
	if(t = rs[u]) {
		xl[u] = xl[u] < xl[t] ? xl[u] : xl[t];
		xr[u] = xr[u] > xr[t] ? xr[u] : xr[t];
		yl[u] = yl[u] < yl[t] ? yl[u] : yl[t];
		yr[u] = yr[u] > yr[t] ? yr[u] : yr[t];
	}
}
void down(int u) {
	if(~ tag[u]) {
		if(ls[u]) col[ls[u]] = tag[ls[u]] = tag[u];
		if(rs[u]) col[rs[u]] = tag[rs[u]] = tag[u];
		tag[u] = -1;
	}
}
bool cmp(int a, int b) {
	return cmpd ? ( y[a] < y[b] || (y[a] == y[b] && x[a] < x[b]) ) : ( x[a] < x[b] || (x[a] == x[b] && y[a] < y[b]) );
}
int build(int l, int r, int d = 0) {
	if(l > r) return 0;
	int mid = (l + r) >> 1; cmpd = d;
	nth_element(p + l, p + mid, p + r + 1, cmp);
	int u = p[mid];
	col[u] = 1; tag[u] = -1;
	ls[u] = build(l, mid - 1, d ^ 1);
	rs[u] = build(mid + 1, r, d ^ 1);
	upd(u); return u;
}
struct Edge { int v, nxt; } e[N * 2];
int hd[N], ec;
void clr() {
	ec = 0; fill(hd + 1, hd + n + 1, -1);
}
void add(int u, int v) {
	e[ec] = (Edge) {v, hd[u]}; hd[u] = ec ++;
}
void dfs(int u) {
	static int idx; y[u] = ++ idx;
	for(int i = hd[u]; ~ i; i = e[i].nxt) {
		x[e[i].v] = x[u] + 1; dfs(e[i].v);
	}
	dr[u] = idx;
}
int qry(int qu) {
	int u = rt; cmpd = 0;
	for(; u ^ qu; cmpd ^= 1) {
		down(u);
		u = cmp(qu, u) ? ls[u] : rs[u];
	}
	return col[u];
}
//[ x[qu], x[qu] + len ] [ y[qu], dr[qu] ]
void modify(int u, int qu, int len, int c) {
	if(u == 0 || x[qu] + len < xl[u] || x[qu] > xr[u] || dr[qu] < yl[u] || y[qu] > yr[u]) return ;
	if(x[qu] <= xl[u] && xr[u] <= x[qu] + len && y[qu] <= yl[u] && yr[u] <= dr[qu]) {
		tag[u] = col[u] = c; return ;
	}
	if(x[qu] <= x[u] && x[u] <= x[qu] + len && y[qu] <= y[u] && y[u] <= dr[qu]) {
		col[u] = c;
	}
	down(u); modify(ls[u], qu, len, c); modify(rs[u], qu, len, c);
}
int main() {
	// freopen("input", "r", stdin);
	int T; scanf("%d", &T);
	while(T --) {
		scanf("%d%d%d", &n, &m, &q); clr();
		for(int f, i = 2; i <= n; i ++) {
			scanf("%d", &f); add(f, i);
		}
		for(int i = 1; i <= n; i ++) p[i] = i;
		dfs(1); rt = build(1, n); int ans = 0;
		for(int u, l, c, i = 1; i <= q; i ++) {
			scanf("%d%d%d", &u, &l, &c);
			if(c == 0) (ans += 1ll * i * qry(u) % mo) %= mo;
			else modify(rt, u, l, c);
		}
		printf("%d\n", ans);
	}
	return 0;
}