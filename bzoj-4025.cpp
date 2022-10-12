#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 1e5 + 10;
int n, m, t;
vector< pair<int, int> > G[N << 2];
bool ans[N];
void addedge(int u, int l, int r, int ql, int qr, pair<int, int> p) {
	if(l == ql && r == qr) { G[u].push_back(p); return ; }
	int mid = (l + r) >> 1;
	if(qr <= mid) addedge(u << 1, l, mid, ql, qr, p);
	else if(ql > mid) addedge(u << 1 | 1, mid + 1, r, ql, qr, p);
	else {
		addedge(u << 1, l, mid, ql, mid, p);
		addedge(u << 1 | 1, mid + 1, r, mid + 1, qr, p);
	}
}
int f[N * 2], sz[N * 2], top, st[N * 2][2];
void init() {
	for(int i = 1; i <= 2 * n; i ++) {
		f[i] = i; sz[i] = 1;
	}
}
int find(int u) {
	while(u ^ f[u]) u = f[u];
	return u;
}
bool merge(int u, int v) {
	u = find(u); v = find(v);
	if(u == v) return 0;
	if(sz[u] < sz[v]) swap(u, v);
	f[v] = u; sz[u] += sz[v];
	top ++; st[top][0] = u; st[top][1] = v;
	return 1;
}
void pop(int t) {
	while(top > t) {
		int u = st[top][0], v = st[top][1];
		sz[u] -= sz[v]; f[v] = v;
		top --;
	}
}
bool linked(int u, int v) {
	return find(u) == find(v);
}
void solve(int u, int l, int r) {
	int ptop = top;
	for(int i = 0; i < (int) G[u].size(); i ++) {
		int x = G[u][i].first, y = G[u][i].second;
		if(linked(x, y)) {
			pop(ptop); return ;
		}
		merge(x, y + n); merge(x + n, y);
	}
	if(l == r) ans[l] = 1;
	else {
		int mid = (l + r) >> 1;
		solve(u << 1, l, mid);
		solve(u << 1 | 1, mid + 1, r);
	}
	pop(ptop);
}
int main() {
	scanf("%d%d%d", &n, &m, &t);
	for(int i = 1; i <= m; i ++) {
		int u, v, l, r;
		scanf("%d%d%d%d", &u, &v, &l, &r);
		if(l ^ r) addedge(1, 1, t, l + 1, r, pair<int, int>(u, v));
	}
	init(); solve(1, 1, t);
	for(int i = 1; i <= t; i ++)
		puts(ans[i] ? "Yes" : "No");
	return 0;
}