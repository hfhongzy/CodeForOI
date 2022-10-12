#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
const int M = 2e6 + 10;
int id, n, la, c, nxt[M][10], len[M], lnk[M], a[N];
vector<int> G[N];
void clr(int x) { fill(nxt[x], nxt[x] + c, -1); }
void init() { id = len[0] = 0; lnk[0] = -1; clr(0); }
int extend(int la, int nc) {
	int u = ++ id, p = la;
	len[u] = len[la] + 1; clr(u);
	for(; ~ p && -1 == nxt[p][nc]; p = lnk[p]) {
		nxt[p][nc] = u;
	}
	if(p == -1) lnk[u] = 0;
	else {
		int q = nxt[p][nc];
		if(len[p] + 1 == len[q]) {
			lnk[u] = q;
		} else {
			int q0 = ++ id;
			copy(nxt[q], nxt[q] + c, nxt[q0]);
			len[q0] = len[p] + 1; lnk[q0] = lnk[q];
			lnk[q] = lnk[u] = q0;
			for(; ~ p && nxt[p][nc] == q; p = lnk[p]) {
				nxt[p][nc] = q0;
			}
		}
	}
	return u;
}
void dfs(int u, int fa, int p) {
	int now = extend(p, a[u]);
	for(int i = 0; i < (int) G[u].size(); i ++) {
		int v = G[u][i];
		if(v == fa) continue ;
		dfs(v, u, now);
	}
}
int main() {
	freopen("input", "r", stdin);
	scanf("%d%d", &n, &c);
	for(int i = 1; i <= n; i ++) scanf("%d", a + i);
	for(int u, v, i = 1; i < n; i ++) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	init();
	for(int i = 1; i <= n; i ++) {
		if(G[i].size() == 1) {
			dfs(i, -1, 0);
		}
	}
	ll ans = 0;
	for(int i = id; i >= 1; i --) {
		ans += len[i] - len[lnk[i]];
	}
	printf("%lld\n", ans);
	return 0;
}