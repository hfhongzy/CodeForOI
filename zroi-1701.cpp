#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef long long ll;

const int N = 1e6 + 10;
const int mod = 998244353;

int n, m, q, lgn, seq[N], k, cnt[N], cr[N], sz[N];
int dfn[N], low[N], st[N], top, idx;
vector<int> G[N], T[N];
int id, f[N][21], d[N];
void tarjan(int u) {
  st[++ top] = u; low[u] = dfn[u] = ++ idx;
  for(int v : G[u]) {
    if(!dfn[v]) {
      tarjan(v); low[u] = min(low[u], low[v]);
      if(low[v] == dfn[u]) {
        id ++;
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
void dfs(int u, int fa = 0) {
  f[u][0] = fa; d[u] = d[fa] + 1; dfn[u] = ++ idx;
  cr[u] = cr[fa] + (u <= n);
  rep(i, 1, lgn) {
    f[u][i] = f[f[u][i - 1]][i - 1];
    if(!f[u][i]) break ;
  }
  for(int v : T[u]) if(v ^ fa) dfs(v, u);
}
int LCA(int u, int v) {
  if(d[u] < d[v]) swap(u, v);
  int c = d[u] - d[v];
  per(i, lgn - 1, 0) if(c >> i & 1) u = f[u][i];
  if(u == v) return u;
  per(i, lgn - 1, 0) if(f[u][i] ^ f[v][i]) {
    u = f[u][i]; v = f[v][i];
  }
  return f[u][0];
}
vector<int> v[N];
void insert(int u) {
  if(top == 1) { st[++ top] = u; return ; }
  int x = LCA(u, st[top]);
  if(x == st[top]) { st[++ top] = u; return ; }
  while(top >= 2 && d[st[top - 1]] > d[x]) {
    v[st[top - 1]].pb(st[top]); top --;
  }
  v[x].pb(st[top]); top --;
  if(st[top] != x) st[++ top] = x;
  st[++ top] = u;
}
ll ans, dp[N];
void vir(int u) {
  sz[u] = cnt[u];
  for(int v : ::v[u]) {
    vir(v); sz[u] += sz[v];
  }
  if(u != 1) dp[1] += (ll)cnt[u] * (cr[u] - 1);
}
void vir2(int u, int fa = 0) {
  if(fa) {
    dp[u] = dp[fa] - (cr[u] - cr[fa]) * (ll)sz[u];
    dp[u] += (cr[u] - cr[fa] - (u <= n) + (fa <= n)) * (ll)(k - sz[u]);
  }
  if(u <= n) ans = min(ans, dp[u]);
  else ans = min(ans, dp[u] - (k - sz[u]));
  for(int v : ::v[u]) {
    int t = sz[v];
    vir2(v, u);
    if(u > n) {
      ans = min(ans, dp[u] - t);
    }
  }
  dp[u] = sz[u] = cnt[u] = 0; v[u].clear();
}
int main() {
  scanf("%d%d%d", &n, &m, &q); id = n;
  rep(i, 1, m) {
    int u, v;
    scanf("%d%d", &u, &v);
    G[u].pb(v); G[v].pb(u);
  }
  tarjan(1);
  for(lgn = 1; (1 << lgn) <= id; lgn ++) ;
  idx = 0; dfs(1);
  rep(i, 1, q) {
    scanf("%d", &k);
    rep(j, 1, k) {
      scanf("%d", seq + j); cnt[seq[j]] ++;
    }
    sort(seq + 1, seq + k + 1, [&](int x, int y) {
      return dfn[x] < dfn[y];
    });
    st[top = 1] = 1; seq[0] = 1;
    rep(j, 1, k) if(seq[j] != seq[j - 1]) insert(seq[j]);
    rep(j, 1, top - 1) v[st[j]].pb(st[j + 1]);
    ans = 1ll << 62; vir(1); vir2(1);
    printf("%lld\n", (n - 1ll) * k - ans);
  }
  return 0;
}