#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int n, m, s, w[N], c[N], u[N], v[N], p[N], f[N], x[N];
bool tag[N];
vector<int> G[N];
bool cmp(int x, int y) { return w[x] < w[y]; }
int find(int u) {
	return u == f[u] ? u : f[u] = find(f[u]);
}
bool unite(int u, int v) {
	u = find(u); v = find(v); f[u] = v;
	return u == v ? 0 : 1;
}
int fa[N], top[N], d[N], son[N], sz[N], pos[N], idx, dfn[N], lnk[N];
void dfs1(int u) {
	sz[u] = 1; d[u] = d[fa[u]] + 1;
	for(int e : G[u]) if((x[e] ^ u) != fa[u]) {
		int v = x[e] ^ u; lnk[v] = e;
		fa[v] = u; dfs1(v); sz[u] += sz[v];
		if(sz[v] > sz[son[u]]) son[u] = v;
	}
}
void dfs2(int u, int t) {
	top[u] = t; dfn[u] = ++ idx; pos[idx] = u;
	if(son[u]) {
		dfs2(son[u], t);
		for(int e : G[u]) if(!dfn[x[e] ^ u]) dfs2(x[e] ^ u, x[e] ^ u);
	}
}
int st[N][20], lg[N];
int stmax(int u, int v) {
	return u == -1 ? v : (w[lnk[u]] > w[lnk[v]] ? u : v);
}
void buildst() {
	lg[1] = 0;
	for(int i = 2; i <= n; i ++) lg[i] = lg[i >> 1] + 1;
	for(int i = 1; i <= n; i ++) st[i][0] = pos[i];
	for(int j = 1; j <= lg[n]; j ++) {
		for(int i = 1; i + (1 << j) - 1 <= n; i ++) {
			st[i][j] = stmax(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
		}
	}
}
int queryst(int l, int r) {
	int k = lg[r - l + 1];
	return stmax(st[l][k], st[r - (1 << k) + 1][k]);
}
int qmax(int u, int v, int &eid) {
	int ans = -1;
	while(top[u] ^ top[v]) {
		if(d[top[u]] < d[top[v]]) swap(u, v);
		ans = stmax(ans, queryst(dfn[top[u]], dfn[u]));
		u = fa[top[u]];
	}
	if(dfn[u] > dfn[v]) swap(u, v);
	if(dfn[u] ^ dfn[v]) {
		ans = stmax(ans, queryst(dfn[u] + 1, dfn[v]));
	}
	eid = lnk[ans];
	return w[eid];
}
int main() {
	freopen("input", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i ++) scanf("%d", w + i);
	for(int i = 1; i <= m; i ++) scanf("%d", c + i);
	for(int i = 1; i <= m; i ++) scanf("%d%d", u + i, v + i), x[i] = u[i] ^ v[i];
	for(int i = 1; i <= m; i ++) p[i] = i;
	for(int i = 1; i <= n; i ++) f[i] = i;
	sort(p + 1, p + m + 1, cmp);
	int cnt = 0, mc = 2e9, dec = 0; ll ans = 0, ans2 = 0;
	for(int i = 1; i <= m; i ++) if(unite(u[p[i]], v[p[i]])) {
		cnt ++; tag[p[i]] = 1; ans += w[p[i]];
		G[u[p[i]]].push_back(p[i]);
		G[v[p[i]]].push_back(p[i]);
		mc = min(mc, c[p[i]]);
		if(mc == c[p[i]]) dec = p[i];
		if(cnt == n - 1) break ;
	}
	int from = -1, to = -1;
	scanf("%d", &s); ans2 = ans - (s / mc); dfs1(1); dfs2(1, 1); buildst();
	for(int i = 1; i <= m; i ++) if(!tag[i] && mc > c[i]) {
		int eid = 0;
		ll res = ans - qmax(u[i], v[i], eid) + w[i] - (s / c[i]);
		if(res < ans2) {
			ans2 = res; from = eid; to = dec = i;
		}
	}
	if(~ to) swap(tag[to], tag[from]);
	printf("%lld\n", ans2);
	for(int i = 1; i <= m; i ++) if(tag[i]) {
		if(dec == i) w[i] -= s / c[i];
		printf("%d %d\n", i, w[i]);
	}
	return 0;
}