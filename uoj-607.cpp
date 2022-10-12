#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
const int mod = 998244353;
int n, f[N], g[N], inv[N], sz[N], l[N];
vector<int> G[N];
void dfs(int u, int fa = 0) {
  sz[u] = 1;
  for(int v : G[u]) if(v ^ fa) { dfs(v, u); sz[u] += sz[v]; }
  int pd = 1;
  for(int v : G[u]) if(v ^ fa) {
    l[v] = pd; pd = (ll)pd * f[v] % mod;
  }
  g[u] = pd; pd = 1;
  for(int i = int(G[u].size()) - 1; ~i; i --) {
    int v = G[u][i];
    if(v ^ fa) {
      g[u] = (g[u] + (ll)l[v] * pd % mod * inv[sz[u] - sz[v]] % mod * g[v]) % mod;
      pd = (ll)pd * f[v] % mod;
    }
  }
  f[u] = (ll)g[u] * inv[sz[u]] % mod;
}
int main() {
  scanf("%d", &n);
  int u, v;
  rep(i, 1, n - 1) {
    scanf("%d%d", &u, &v);
    G[u].pb(v); G[v].pb(u);
  }
  inv[1] = 1;
  rep(i, 2, n) inv[i] = (mod - mod / i) * (ll)inv[mod % i] % mod;
  dfs(1);
  int ans = 1;
  rep(i, 1, n - 1) ans = (ll)ans * i % mod;
  for(int v : G[1]) ans = (ll)ans * f[v] % mod;
  printf("%d\n", ans);
  return 0;
}