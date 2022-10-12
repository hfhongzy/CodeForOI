#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
const int mod = 998244353;
int add(int a, int b) {
  return (a += b) >= mod ? a -= mod : a;
}
int n, m, d[N];
bool fix[N];
vector<int> G[N], T[N];
struct extra { int u, v; };
vector<extra> e;
struct coef {
  int a, b;
  void operator *= (const int &c) {
    a = (ll)a * c % mod;
    b = (ll)b * c % mod;
  }
  coef operator + (const coef &rhs) {
    return coef{add(a, rhs.a), add(b, rhs.b)};
  }
  int calc(int x, int y) {
    return ((ll)a * x + (ll)b * y) % mod;
  }
} f[N][2];
int low[N], top[N], g[N][2], dp[N][2], rt;
void dfs(int u) {
  for(int v : G[u]) {
    if(!d[v]) {
      d[v] = d[u] + 1; dfs(v);
    } else if(d[v] < d[u] - 1) {
      low[u] = u; low[v] = v;
      e.pb({u, v});
    }
  }
}
void dfs2(int u) {
  f[u][0] = {1, 0}; f[u][1] = {0, 1};
  g[u][0] = g[u][1] = 1;
  int cs = 0;
  for(int v : G[u]) {
    if(d[v] == d[u] + 1) {
      dfs2(v);
      if(!low[v]) {
        g[u][0] = (ll)g[u][0] * (g[v][0] + g[v][1]) % mod;
        g[u][1] = (ll)g[u][1] * g[v][0] % mod;
      } else {
        cs++;
        if(!low[u]) low[u] = low[v];
        if(cs >= 2) low[u] = u;
        else f[u][0] = f[v][0] + f[v][1], f[u][1] = f[v][0];
      }
    }
  }
  if(low[u] && low[u] != u) {
    f[u][0] *= g[u][0];
    f[u][1] *= g[u][1];
  }
  if(low[u] == u) {
    f[u][0] = {1, 0}; f[u][1] = {0, 1};
    if(!rt || d[rt] > d[u]) rt = u;
    for(int v : G[u]) {
      if(d[v] == d[u] + 1 && low[v]) {
        T[u].pb(low[v]);
        top[low[v]] = v;
      }
    }
  }
}
void dfsT(int u) {
  dp[u][0] = g[u][0];
  dp[u][1] = g[u][1];
  for(int v : T[u]) {
    dfsT(v);
    int f0 = f[top[v]][0].calc(dp[v][0], dp[v][1]);
    int f1 = f[top[v]][1].calc(dp[v][0], dp[v][1]);
    dp[u][0] = (ll)dp[u][0] * (f0 + f1) % mod;
    dp[u][1] = (ll)dp[u][1] * f0 % mod;
  }
  if(fix[u]) dp[u][0] = 0;
}
int main() {
  scanf("%d%d", &n, &m);
  int u, v;
  rep(i, 1, m) {
    scanf("%d%d", &u, &v);
    G[u].pb(v); G[v].pb(u);
  }
  rep(i, 1, n) {
    sort(G[i].begin(), G[i].end());
    G[i].resize(unique(G[i].begin(), G[i].end()) - G[i].begin());
  }
  d[1] = 1; dfs(1); low[1] = 1; dfs2(1);
  static int cnt[4096];
  ll ans = 0;
  for(int sz = int(e.size()), i = 0; i < (1 << sz); i ++) {
    if(i) cnt[i] = cnt[i & (i - 1)] ^ 1;
    for(int j = 0; j < sz; j ++)
      if(i >> j & 1) fix[e[j].u] = fix[e[j].v] = 1;
    dfsT(rt);
    ans += (cnt[i] ? -1 : 1) * (dp[rt][0] + dp[rt][1]);
    for(int j = 0; j < sz; j ++)
      if(i >> j & 1) fix[e[j].u] = fix[e[j].v] = 0;
  }
  if((ans %= mod) < 0) ans += mod;
  printf("%d\n", int(ans));
  return 0;
}