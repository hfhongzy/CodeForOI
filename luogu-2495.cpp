#include <algorithm>
#include <cstdio>
#include <vector>
#define pb push_back
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;
const ll INF = 1e18 + 10;
int n, q, lgn, f[N][20], d[N];
struct Edge { int v, w; };
vector<Edge> G[N];
int dfn[N], idx;
ll Min[N], dp[N];
void dfs(int u, int fa = 0) {
	dfn[u] = ++ idx; f[u][0] = fa; d[u] = d[fa] + 1;
	for(int i = 1; i < lgn; i ++) f[u][i] = f[f[u][i - 1]][i - 1];
	for(int i = 0; i < (int) G[u].size(); i ++) {
		Edge &e = G[u][i];
		if(e.v ^ fa) {
			Min[e.v] = min(Min[u], (ll) e.w);
			dfs(e.v, u);
		}
	}
}
int lca(int u, int v) {
	if(d[u] < d[v]) swap(u, v);
	int c = d[u] - d[v];
	for(int i = lgn - 1; ~ i; i --)
		if(c >> i & 1) u = f[u][i];
	if(u == v) return u;
	for(int i = lgn - 1; ~ i; i --)
		if(f[u][i] ^ f[v][i]) {
			u = f[u][i]; v = f[v][i];
		}
	return f[u][0];
}
bool cmp(int x, int y) { return dfn[x] < dfn[y]; }
int top, st[N];
vector<int> T[N];
void ins(int u) {
	if(u == 1) return ;
	if(top == 1) { st[++ top] = u; return ; }
	int l = lca(u, st[top]);
	if(l != st[top]) {
		while(dfn[l] < dfn[st[top - 1]]) {
			T[st[top - 1]].pb(st[top]); top --;
		}
		if(dfn[l] > dfn[st[top - 1]]) {
			T[l].pb(st[top]); st[top] = l;
		} else {
			T[l].pb(st[top]); top --;
		}
	}
	st[++ top] = u;
}
bool use[N];
void Tdfs(int u, int fa = 0) {
	ll s = 0;
	for(int i = 0; i < (int) T[u].size(); i ++) {
		int v = T[u][i];
		if(v != fa) { Tdfs(v, u); s += dp[v]; }
	}
	dp[u] = use[u] ? Min[u] : min(Min[u], s);
	T[u].clear();
}
void build() {
	static int a[N], m; scanf("%d", &m);
	for(int i = 1; i <= m; i ++) { scanf("%d", a + i); use[a[i]] = 1; }
	sort(a + 1, a + m + 1, cmp);
	st[top = 1] = 1;
	for(int i = 1; i <= m; i ++) ins(a[i]);
	for(int i = 1; i < top; i ++) T[st[i]].pb(st[i + 1]);
	Tdfs(1); printf("%lld\n", dp[1]);
	for(int i = 1; i <= m; i ++) use[a[i]] = 0;
}
int main() {
	scanf("%d", &n);
	for(lgn = 1; (1 << lgn) <= n; lgn ++) ;
	for(int i = 1; i < n; i ++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		G[u].pb((Edge) {v, w});
		G[v].pb((Edge) {u, w});
	}
	Min[1] = INF; dfs(1);
	scanf("%d", &q);
	while(q --) build();
	return 0;
}