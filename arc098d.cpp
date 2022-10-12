#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, m, a[N], b[N], p[N], f[N];
vector<int> G[N], T[N];
ll dp[N], s[N];
int find(int u) {
  return u == f[u] ? u : f[u] = find(f[u]);
}
void dfs(int u) {
  s[u] = b[u];
  dp[u] = T[u].size() ? (1ll << 61) : max(0, a[u] - b[u]);
  for(int v : T[u]) {
    dfs(v);
    s[u] += s[v];
    dp[u] = min(dp[u], dp[v] + max(0ll, a[u] - b[u] - s[v] - dp[v]));
  }
}
int main() {
  scanf("%d%d", &n, &m);
  ll sum = 0;
  rep(i, 1, n) scanf("%d%d", a + i, b + i);
  int u, v;
  rep(i, 1, m) {
    scanf("%d%d", &u, &v);
    G[u].pb(v); G[v].pb(u);
  }
  rep(i, 1, n) p[i] = i;
  sort(p + 1, p + n + 1, [&](int x, int y) { return a[x] - b[x] <= a[y] - b[y]; });
  rep(i, 1, n) {
    int u = p[i]; f[u] = u;
    for(int v : G[u]) if(f[v]) {
      v = find(v);
      if(f[v] != u) {
        T[u].pb(v); f[v] = u;
      }
    }
  }
  int rt = 0;
  rep(i, 1, n) if(find(i) == i) rt = i;
  dfs(rt);
  printf("%lld\n", s[rt] + dp[rt]);
  return 0;
}