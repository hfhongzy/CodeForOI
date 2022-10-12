#include <bits/stdc++.h>
#define pb push_back
#define debug(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;
const int mod = 998244353;

int n, rt, dp[N][2], inv[N], w[N], g[N][2], h[N];
vector<int> G[N];
void dfs(int u, int fa = 0) {
  for(int v : G[u]) if(v ^ fa) {
    dfs(v, u);
    (h[u] += inv[G[v].size()]) %= mod;
  }
  rep(t, 0, 1) {
    if(G[u].size() == 1 && fa) {
      dp[u][t] = !t ? 0 : w[u];
      g[u][t] = 0;
      continue ;
    }
    int s1 = 0, s0 = 0;
    for(int v : G[u]) if(v ^ fa) {
      (s1 += dp[v][1]) %= mod;
      (s0 += dp[v][0]) %= mod;
    }
    dp[u][t] = (ll)s0 * inv[G[u].size() - t] % mod;
    for(int v : G[u]) if(v ^ fa) {
      int t3 = g[v][0] * (ll)inv[G[v].size() - 1] % mod * inv[G[u].size() - t] % mod; //>=3 step
      int t2 = h[v] * (ll)inv[G[u].size() - t] % mod * inv[G[v].size()] % mod * inv[G[v].size()] % mod;
      int t1 = inv[G[u].size() - t] * (ll)inv[G[v].size()] % mod;
      // printf("fa = %d, son = %d, t 1 2 3 = %d %d %d\n", u, v, t1, t2, t3);
      int cur = (s1 + mod - dp[v][1]) * ((ll)t3 + t2 + t1) % mod;
      (dp[u][t] += cur) %= mod;
      cur = dp[v][1] * (ll)inv[G[u].size() - t] % mod * inv[G[u].size() - t] % mod * inv[G[v].size()] % mod;
      (dp[u][t] += cur) %= mod;
      g[u][t] = (g[u][t] + (ll)t2 + t3) % mod;
    }
  }
  // printf("g[%d][0 & 1] = %d %d\n", u, g[u][0], g[u][1]);
  // printf("dp[%d][0 & 1] = %d %d\n", u, dp[u][0], dp[u][1]);
}
int main() {
  scanf("%d%d", &n, &rt);
  rep(i, 1, n) scanf("%d", w + i);
  if(n == 1) return printf("%d\n", w[1]), 0;
  inv[1] = 1;
  rep(i, 2, n) inv[i] = (mod - mod / i) * (ll)inv[mod % i] % mod;
  int x, y;
  rep(i, 1, n - 1) {
    scanf("%d%d", &x, &y);
    G[x].pb(y); G[y].pb(x);
  }
  dfs(rt);
  printf("%d\n", dp[rt][0]);
  return 0;
}