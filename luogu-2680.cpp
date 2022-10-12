#include <algorithm>
#include <cstdio>
#include <vector>
#define fs first
#define sc second
using namespace std;
typedef pair<int, int> pii;
const int N = 3e5 + 10;
int n, lgn, m, a[N], b[N], p[N], c[N], d[N], de[N], lc[N], tg[N], fw[N];
int lg[N], f[N][20];
vector<pii> G[N];
void dfs(int u, int fa = 0) {
	f[u][0] = fa;
	for(int i = 1; i < lgn; i ++)
		if(!(f[u][i] = f[f[u][i - 1]][i - 1])) break ;
	for(int i = 0; i < (int) G[u].size(); i ++) {
		pii &e = G[u][i];
		if(e.fs != fa) {
			de[e.fs] = de[u] + e.sc;
			d[e.fs] = d[u] + 1;
			fw[e.fs] = e.sc;
			dfs(e.fs, u);
		}
	}
}
int lca(int u, int v) {
	if(d[u] < d[v]) swap(u, v);
	int c = d[u] - d[v];
	for(; c; c &= c - 1) u = f[u][lg[c & (-c)]];
	if(u == v) return u;
	for(int i = lgn - 1; ~ i; i --)
		if(f[u][i] ^ f[v][i]) {
			u = f[u][i]; v = f[v][i];
		}
	return f[u][0];
}
int maxw, tot, up;
bool dfs2(int u) {
	for(int i = 0; i < (int) G[u].size(); i ++) {
		pii &e = G[u][i];
		if(e.fs != f[u][0]) {
			if(dfs2(e.fs)) return 1;
			tg[u] += tg[e.fs];
		}
	}
	if(tg[u] == tot && fw[u] >= up) return 1;
	return 0;
}
bool check(int mid) {
	up = tot = maxw = 0;
	fill(tg + 1, tg + n + 1, 0);
	for(int i = m; i >= 1; i --) {
		int u = p[i];
		if(c[u] <= mid) break ;
		up = max(up, c[u] - mid); tot ++;
		tg[b[u]] ++; tg[a[u]] ++; tg[lc[u]] -= 2;
	}
	if(up == 0) return 1;
	return dfs2(1);
}
bool cmp(int x, int y) { return c[x] < c[y]; }
int main() {
	scanf("%d%d", &n, &m);
	for(lgn = 1; (1 << lgn) <= n; lgn ++) ;
	for(int i = 0; i < lgn; i ++) lg[1 << i] = i;
	for(int i = 1; i < n; i ++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		G[u].push_back(pii(v, w));
		G[v].push_back(pii(u, w));
	}
	dfs(1);
	for(int i = 1; i <= m; i ++) {
		scanf("%d%d", a + i, b + i); p[i] = i;
		c[i] = de[a[i]] + de[b[i]] - 2 * de[lc[i] = lca(a[i], b[i])];
	}
	sort(p + 1, p + m + 1, cmp);
	int l = 0, r = *max_element(c + 1, c + m + 1), ans = 0;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(check(mid)) r = (ans = mid) - 1;
		else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}