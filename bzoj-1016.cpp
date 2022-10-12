#include <algorithm>
#include <cstdio>
using namespace std;
const int mod = 31011, N = 1100;
struct Edge {
	int u, v, w;
} e[N];
int n, m, b[N];
struct ufs {
	int f[105];
	void init() {
		for(int i = 1; i <= n; i ++) f[i] = i;
	} 
	int find(int u) {
		return u == f[u] ? u : f[u] = find(f[u]);
	}
	bool unite(int u, int v) {
		u = find(u); v = find(v);
		if(u == v) return 0;
		return f[u] = v, 1;
	}
} a, t;
bool kruskal() {
	t.init(); int cur = 0;
	for(int i = 1; i <= m; i ++) {
		if(t.unite(e[i].u, e[i].v)) {
			b[++ cur] = e[i].w;
			if(cur == n - 1) break ;
		}
	}
	return cur == n - 1;
}
bool cmp(const Edge &a, const Edge &b) { return a.w < b.w; }
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i ++)
		scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
	sort(e + 1, e + m + 1, cmp);
	if(!kruskal()) { puts("0"); return 0; }
	int ans = 1; t.init();
	for(int i = 1, j; i <= m; i = j + 1) {
		j = i;
		for(; j < m && e[j + 1].w == e[i].w; j ++) ;
		int cnt = upper_bound(b + 1, b + n, e[i].w) - lower_bound(b + 1, b + n, e[i].w);
		if(!cnt) continue ;
		int cur = 0;
		for(int st = 1; st < (1 << (j - i + 1)); st ++) if(__builtin_popcount(st) == cnt) {
			a = t; cur ++;
			for(int k = 0; k < j - i + 1; k ++) if(st >> k & 1) {
				if(!a.unite(e[i + k].u, e[i + k].v)) {
					cur --; break ;
				}
			}
		}
		ans = ans * cur % mod;
		for(int k = i; k <= j; k ++) t.unite(e[k].u, e[k].v);
	}
	printf("%d\n", ans);
	return 0;
}
