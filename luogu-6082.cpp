#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1e5 + 10;
int n, w[N], t[N], dp[N], g[N];
vector<int> G[N];
void dfs(int u, int fa = 0) {
  dp[u] = w[u]; g[u] = 1;
  if(fa) G[u].erase(find(G[u].begin(), G[u].end(), fa));
  int sz = int(G[u].size());
  for(int v : G[u]) {
    dfs(v, u);
  }
  sort(G[u].begin(), G[u].end(), [&](int x, int y) {
    return dp[x] > dp[y];
  });
  for(int i = 0; i < sz && i < t[u]; i ++) {
    int v = G[u][i];
    if(dp[v] < 0) break ;
    dp[u] += dp[v];
    if(g[v] == 2) g[u] = 2;
    if(!dp[v]) g[u] = 2;
  }
}
int main() {
  scanf("%d", &n); t[1] = n;
  rep(i, 2, n) scanf("%d", w + i);
  rep(i, 2, n) scanf("%d", t + i), t[i] --;
  int u, v;
  rep(i, 1, n - 1) {
    scanf("%d%d", &u, &v);
    G[u].pb(v); G[v].pb(u);
  }
  dfs(1);
  printf("%d\n", dp[1]);
  puts(g[1] == 1 ? "solution is unique" : "solution is not unique");
  return 0;
}