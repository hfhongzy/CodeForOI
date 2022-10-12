#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
using ull = unsigned long long;
const int N = 1e5 + 10;
struct Edge { int v, id; };
int n, m, vis[N], tim, eid[N], cnt[N * 2];
vector<Edge> G[N], T[N];
int main() {
  while(~ scanf("%d%d", &n, &m)) {
    rep(i, 1, n) {
      vector<Edge>().swap(G[i]);
      vector<Edge>().swap(T[i]);
    }
    int u, v;
    rep(i, 1, m) {
      cnt[i] = 0;
      scanf("%d%d", &u, &v);
      G[u].pb({v, i}); G[v].pb({u, i});
    }
    rep(i, 1, n) for(Edge &e : G[i]) if(i < e.v) {
      if(G[i].size() >= G[e.v].size()) T[i].pb({e.v, e.id});
      else T[e.v].pb({i, e.id});
    }
    ull ans = 0;
    rep(i, 1, n) {
      ++ tim;
      for(Edge &e : T[i]) vis[e.v] = tim, eid[e.v] = e.id;
      for(Edge &e1 : T[i]) for(Edge &e2 : T[e1.v]) if(vis[e2.v] == tim) {
        cnt[eid[e2.v]] ++; cnt[e2.id] ++; cnt[e1.id] ++;
      }
    }
    rep(i, 1, m) ans += cnt[i] * (cnt[i] - 1) / 2;
    printf("%llu\n", ans);
  }
  return 0;
}