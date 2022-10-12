#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 2e4 + 10;
const int INF = 2e9;
struct edge {
  int u, v, w;
} e[N];
int n, m, r, ans, Min[N], p[N], bel[N], scc, vis[N], tim;
int main() {
  scanf("%d%d%d", &n, &m, &r);
  int u, v, w;
  rep(i, 1, m) {
    scanf("%d%d%d", &u, &v, &w);
    e[i] = {u, v, w};
  }
  while(1) {
    fill(Min + 1, Min + n + 1, INF);
    rep(i, 1, m) if(e[i].w < Min[e[i].v]) {
      Min[e[i].v] = e[i].w; p[e[i].v] = e[i].u;
    }
    fill(bel + 1, bel + n + 1, 0); scc = 0;
    rep(i, 1, n) if(i != r) {
      if(Min[i] >= INF) {
        puts("-1"); return 0;
      }
      ans += Min[i]; ++ tim;
      for(u = i; u != r && !bel[u] && vis[u] < tim; u = p[u]) vis[u] = tim;
      if(u == r || bel[u]) continue ;
      ++ scc;
      for(; !bel[u]; u = p[u]) bel[u] = scc;
    }
    if(!scc) break ;
    rep(i, 1, n) if(!bel[i]) bel[i] = ++ scc;
    int t = 0;
    rep(i, 1, m) if(bel[e[i].v] != bel[e[i].u])
      e[++ t] = {bel[e[i].u], bel[e[i].v], e[i].w - Min[e[i].v]};
    r = bel[r]; n = scc; m = t;
  }
  printf("%d\n", ans);
  return 0;
}