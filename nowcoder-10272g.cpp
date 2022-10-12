#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e6 + 10, M = 1024, base = 1e6 + 7, mod = 1e9 + 7;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, -1, 0, 1};
int n, m, id, c, tot;
int bel[N], dfn[N], low[N], st[N], top, idx, f[N];
int gas[N], tot_gas[N], sz[N], tot_sz[N];
vector<int> T[N];
char s[M][M];
int ID(int x, int y) { return (x - 1) * n + y; }
bool valid(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= n; }
void tarjan(int x, int y) {
	int u = ID(x, y); bel[u] = c;
	st[++ top] = u; low[u] = dfn[u] = ++ idx;
	rep(d, 0, 3) {
		int nx = x + dx[d], ny = y + dy[d];
		if(!valid(nx, ny) || s[nx][ny] != 'o') continue ;
		int v = ID(nx, ny);
		if(!dfn[v]) {
			tarjan(nx, ny); low[u] = min(low[u], low[v]);
			if(low[v] == dfn[u]) {
				id ++; T[id].clear();
				while(1) {
					int x = st[top --];
					T[x].pb(id); T[id].pb(x);
					if(x == v) break ;
				}
				T[u].pb(id); T[id].pb(u);
			}
		} else low[u] = min(low[u], dfn[v]);
	}
}
void solve(int u, int fa = 0) {
	if(u > n * n) gas[u] = 0;
	sz[u] = (u <= n * n); f[u] = fa;
	for(int v : T[u]) if(v != fa) {
		solve(v, u); gas[u] += gas[v]; sz[u] += sz[v];
	}
	// printf("%d : fa = %d, gas = %d, sz = %d\n", u, fa, gas[u], sz[u]);
}
int fir;
int black(int x, int y) {
	int ans = fir, ss = 0;
	set<int> st;
	rep(d, 0, 3) {
		int nx = x + dx[d], ny = y + dy[d];
		if(valid(nx, ny) && s[nx][ny] == 'o' && !tot_gas[bel[ID(nx, ny)]])
			st.insert(bel[ID(nx, ny)]);
	}
	for(auto it = st.begin(); it != st.end(); it ++) ss += tot_sz[*it];
	ans -= ss;
	bool ok = 1;
	rep(d, 0, 3) {
		int nx = x + dx[d], ny = y + dy[d];
		if(valid(nx, ny) && (s[nx][ny] == '.' || (s[nx][ny] == 'o' && tot_gas[bel[ID(nx, ny)]]))) {
			ok = 0; break ;
		}
	}
	if(ok) ans += 1 + ss;
	return ans;
}
int white(int x, int y) {
	int u = ID(x, y), ans = fir - (tot_gas[bel[u]] == 0 ? tot_sz[bel[u]] : 0);
	for(int v : T[u]) if(v != f[u]) if(!gas[v]) ans += sz[v];
	if(tot_gas[bel[u]] == gas[u]) ans += tot_sz[bel[u]] - sz[u];
	return ans;
}
int main() {
	int test;
	scanf("%d", &test);
	while(test --) {
		scanf("%d", &n);
		rep(i, 1, n) scanf("%s", s[i] + 1);
		rep(i, 1, n * n) bel[i] = gas[i] = dfn[i] = 0, T[i].clear();
		c = 0; id = n * n;
		vector<int> rt;
		rep(i, 1, n) rep(j, 1, n) if(s[i][j] == 'o' && !bel[ID(i, j)]) { c ++; rt.pb(ID(i, j)); tarjan(i, j); }
		rep(i, 1, n) rep(j, 1, n) if(s[i][j] == '.') rep(d, 0, 3) {
			int x = i + dx[d], y = j + dy[d];
			if(valid(x, y)) gas[ID(x, y)] = 1;
		}
		fir = 0;
		for(int u : rt) {
			solve(u); tot_sz[bel[u]] = sz[u]; tot_gas[bel[u]] = gas[u];
		}
		rep(i, 1, c) fir += (tot_gas[i] == 0 ? tot_sz[i] : 0);
		int ans = 0;
		rep(i, 1, n) rep(j, 1, n) if(s[i][j] != '.') {
			// printf("pos %d %d = %d\n", i, j, (s[i][j] == 'o' ? white(i, j) : black(i, j)));
			ans = ((ll)ans * base + (s[i][j] == 'o' ? white(i, j) : black(i, j))) % mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}