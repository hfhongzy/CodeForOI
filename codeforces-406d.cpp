#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, q, fa[N], top[N], d[N], son[N], sz[N];
ll x[N], y[N];
vector<int> G[N];
void dfs1(int u) {
	sz[u] = 1; d[u] = d[fa[u]] + 1;
	for(int v : G[u]) {
		dfs1(v); sz[u] += sz[v];
		if(sz[v] > sz[son[u]]) son[u] = v;
	}
}
void dfs2(int u, int t) {
	top[u] = t;
	if(son[u]) {
		dfs2(son[u], t);
		for(int v : G[u]) if(!top[v]) dfs2(v, v);
	}
}
int lca(int u, int v) {
	while(top[u] ^ top[v]) {
		if(d[top[u]] < d[top[v]]) swap(u, v);
		u = fa[top[u]];
	}
	return d[u] < d[v] ? u : v;
}
ll det(ll x1, ll y1, ll x2, ll y2) { return x1 * y2 - x2 * y1; }
int main() {
	freopen("input", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
		scanf("%lld%lld", x + i, y + i);
	int r = n;
	for(int i = n - 1; i >= 1; i --) {
		if(i != n - 1) {
			r = i + 1;
			while(r < n) {
				if(det(x[r] - x[i], y[r] - y[i], x[fa[r]] - x[r], y[fa[r]] - y[r]) > 0) {
					r = fa[r];
				} else break ;
			}
		}
		fa[i] = r; G[r].push_back(i);
	}
	scanf("%d", &q); dfs1(n); dfs2(n, n);
	for(int x, y, i = 1; i <= q; i ++) {
		scanf("%d%d", &x, &y);
		printf("%d%c", lca(x, y), " \n"[i == q]);
	}
	return 0;
}