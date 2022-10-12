#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1e5 + 10;
int n, cnt, ans, d[N], a[N], mina[N];
vector<int> G[N];
void dfs(int u, int fa = 0) {
  d[u] = d[fa] + 1;
  for(int v : G[u]) if(v != fa) dfs(v, u);
}
void dfs2(int u, int fa = 0) {
  mina[u] = G[u].size() == 1 ? a[u] : N;
  for(int v : G[u]) if(v != fa) dfs2(v, u), mina[u] = min(mina[u], mina[v]);
}
void dfs3(int u, int s, int fa = 0) {
  if(mina[u] - s >= 1) { s ++; ans --; }
  for(int v : G[u]) if(v != fa) dfs3(v, s, u);
}
int main() {
  scanf("%d", &n);
  if(n == 1) { puts("1"); return 0; }
  int u, v;
  rep(i, 1, n - 1) {
    scanf("%d%d", &u, &v);
    G[u].pb(v); G[v].pb(u);
  }
  dfs(1);
  cnt = ans = n;
  rep(i, 2, n) if(G[i].size() == 1) cnt = min(cnt, d[i]);
  rep(i, 2, n) if(G[i].size() == 1) a[i] = max(0, d[i] - cnt);
  dfs2(1);
  dfs3(1, 0);
  printf("%d\n", ans);
  return 0;
}