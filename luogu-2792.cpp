#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef double db;
const int N = 1000 + 10;
const db INF = 2e9;
struct edge {
  int u, v; db w;
} e[N];
int n, m, r, c[N], p[N], bel[N], scc, vis[N], tim;
db ans, Min[N];
int main() {
  scanf("%d", &n); ++ n; scc = 1;
  int u, v; db w;
  int t = 0;
  rep(i, 1, n - 1) {
    scanf("%lf%d", &w, &v);
    if(!v) continue ;
    bel[i] = ++ scc;
    Min[scc] = w; c[scc] = v;
    e[++ t] = {1, scc, w};
  }
  scanf("%d", &m);
  rep(i, 1, m) {
    scanf("%d%d%lf", &u, &v, &w);
    u = bel[u]; v = bel[v];
    if(u && v) {
      e[++ t] = {u, v, w};
      Min[v] = min(Min[v], w);
    }
  }
  rep(i, 2, scc) ans += Min[i] * (c[i] - 1);
  m = t; n = scc; r = 1;
  // printf("%d!\n", scc);
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
  printf("%.2f\n", ans);
  return 0;
}