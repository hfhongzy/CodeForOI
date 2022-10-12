#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
const int N = 1e5 + 10, mod = 1e9 + 7;
int n, m, st[17][N], lg[N], nn, Map[N * 17], f[N * 17], use[N * 17];
int find(int u) {
	// return u == f[u] ? u : f[u] = find(f[u]);
	int v = u;
	while(v != f[v]) v = f[v];
	while(u != f[u]) { int fa = f[u]; f[u] = v; u = fa; }
	return v;
}
bool unite(int x, int y) {
	x = find(x); y = find(y);
	if(x == y) return 0;
	return f[x] = y, 1;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 2; i <= n; i ++) lg[i] = lg[i >> 1] + 1;
	for(int i = 0; i <= lg[n]; i ++) {
		for(int j = 1; j + (1 << i) - 1 <= n; j ++) {
			st[i][j] = ++ nn; Map[nn] = j; f[nn] = nn;
		}
	}
	for(int i = 1; i <= m; i ++) {
		int l1, r1, l2, r2;
		scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
		int len = r1 - l1 + 1;
		unite(st[lg[len]][l1], st[lg[len]][l2]);
		unite(st[lg[len]][r1 - (1 << lg[len]) + 1], st[lg[len]][r2 - (1 << lg[len]) + 1]);
	}
	for(int i = lg[n]; i >= 1; i --) {
		for(int j = 1; j + (1 << i) - 1 <= n; j ++) {
			int fa = find(st[i][j]);
			if(fa == st[i][j]) continue ;
			unite(st[i - 1][j], st[i - 1][Map[fa]]);
			unite(st[i - 1][j + (1 << (i - 1))], st[i - 1][Map[fa] + (1 << (i - 1))]);
		}
	}
	int ans = -1;
	for(int i = 1; i <= n; i ++)
		if(find(i) == i) ans = ~ ans ? ans * 10ll % mod : 9;
	printf("%d\n", ans);
	return 0;
}