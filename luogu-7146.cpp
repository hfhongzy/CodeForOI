#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
const ll INF = 1e18;
int n, m, a[N], x[N], y[N], z[N];
unordered_map<ll, bool> edge;
int vis[N], tim, st[N]; //1 : no; 2 : yes
struct Edge { int v, w; };
vector<Edge> G[N], T[N], top[N];
vector<int> vec;
void dfs(int u, int fa = 0) {
  vis[u] = ++ tim;
  bool tag = 0;
  for(auto e : G[u]) if(e.v != fa) {
    if(!vis[e.v]) {
      T[u].pb(e);
      dfs(e.v, u);
    } else if(vis[u] < vis[e.v]) {
      top[e.v].pb({u, e.w});
      tag = 1;
    }
  }
  if(tag) vec.pb(u);
}
ll dp[N][2];
void dfs2(int u) {
  dp[u][0] = 0;
  dp[u][1] = a[u];
  for(auto e : T[u]) {
    dfs2(e.v);
    dp[u][0] += max(dp[e.v][0], dp[e.v][1]);
    dp[u][1] += max(dp[e.v][0], dp[e.v][1] - e.w);
  }
  for(auto e : top[u]) if(st[e.v] == 2) dp[u][1] -= e.w;
  if(st[u] == 1) dp[u][1] = -INF;
  if(st[u] == 2) dp[u][0] = -INF;
}
ll solve(int s) {
  vec.clear();
  dfs(s);
  int sz = int(vec.size());
  ll ans = 0;
  for(int i = 0; i < (1 << sz); i ++) {
    for(int j = 0; j < sz; j ++) st[vec[j]] = 1 + (i >> j & 1);
    dfs2(s);
    ans = max(ans, max(dp[s][0], dp[s][1]));
  }
  return ans;
}
int main() {
  int x0, y0, a0, z0;
  const int q = 101, b = 137, p = 1e9 + 7;
  scanf("%d%d%d%d%d%d", &n, &m, &x0, &y0, &a0, &z0);
  a[0] = a0;
  rep(i, 1, n) a[i] = ((ll)q * a[i - 1] + b) % p;
  x[0] = x0; y[0] = y0; z[0] = z0;
  rep(i, 1, m) {
    x[i] = ((ll)q * x[i - 1] + b) % p;
    y[i] = ((ll)q * y[i - 1] + b) % p;
    z[i] = ((ll)q * z[i - 1] + b) % p;
    int u = x[i] % n + 1;
    int v = y[i] % n + 1;
    if(u == v) continue ;
    if(u > v) swap(u, v);
    if(edge.count(u * (1ll << 32) + v)) continue ;
    edge[u * (1ll << 32) + v] = 1;
    G[u].pb({v, z[i]}); G[v].pb({u, z[i]});
  }
  ll ans = 0;
  rep(i, 1, n) if(!vis[i]) ans += solve(i);
  printf("%lld\n", ans);
  return 0;
}