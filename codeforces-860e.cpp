#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;
int n, rt, idx;
int fa[N], top[N], d[N], son[N], sz[N], dfn[N];
vector<int> G[N];
void dfs1(int u) {
	sz[u] = 1; d[u] = d[fa[u]] + 1;
	for(int v : G[u]) {
		dfs1(v); sz[u] += sz[v];
		if(sz[v] > sz[son[u]]) son[u] = v;
	}
}
void dfs2(int u, int t) {
	top[u] = t; dfn[u] = ++ idx;
	if(son[u]) {
		dfs2(son[u], t);
		for(int v : G[u]) if(!dfn[v]) dfs2(v, v);
	}
}
ll bit[2][N], ans[N]; //0 : sum ; 1 : part
void modify(int l, int r) {
	for(int u = r; u <= n; u += u & (-u)) bit[0][u] += r;
	for(int u = r; u <= n; u += u & (-u)) bit[1][u] ++;
	if(! --l) return ;
	for(int u = l; u <= n; u += u & (-u)) bit[0][u] -= l;
	for(int u = l; u <= n; u += u & (-u)) bit[1][u] --;
}
ll query(int r) {
	ll ans = 0;
	for(int u = n; u >= 1; u &= u - 1) ans += bit[1][u];
	for(int u = r; u >= 1; u &= u - 1) ans -= bit[1][u];
	ans *= r;
	for(int u = r; u >= 1; u &= u - 1) ans += bit[0][u];
	return ans;
}
ll query(int l, int r) {
	return query(r) - (l == 1 ? 0 : query(l - 1));
}
void add(int u) {
	while(top[u] ^ rt) {
		modify(dfn[top[u]], dfn[u]);
		u = fa[top[u]];
	}
	modify(1, dfn[u]);
}
ll qsum(int u) {
	ll ans = 0; 
	while(top[u] ^ rt) {
		ans += query(dfn[top[u]], dfn[u]);
		u = fa[top[u]];
	}
	ans += query(1, dfn[u]);
	return ans;
}
bool cmp(int u, int v) { return d[u] < d[v]; }
int main() {
	freopen("input", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) {
		scanf("%d", fa + i);
		if(!fa[i]) rt = i;
		else G[fa[i]].push_back(i);
	}
	d[0] = -1; dfs1(rt); dfs2(rt, rt);
	static int p[N];
	for(int i = 1; i <= n; i ++) p[i] = i;
	sort(p + 1, p + n + 1, cmp);
	for(int i = 1, r; i <= n; i = r + 1) {
		for(r = i; d[p[r + 1]] == d[p[i]]; r ++) ;
		for(int j = i; j <= r; j ++) add(p[j]);
		for(int j = i; j <= r; j ++) ans[p[j]] = qsum(p[j]) - 1 - d[p[j]];
	}
	for(int i = 1; i <= n; i ++)
		printf("%lld%c", ans[i], " \n"[i == n]);
	return 0;
}