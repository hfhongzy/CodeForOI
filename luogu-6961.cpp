#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const ll INF = 1ll << 60;
const int N = 3048;
struct edge { int u, v, w; } e[N];
int n, m;
ll g[N], dp[N][N];
struct Edge { int v, w; };
vector<Edge> G[N];
void clean(int n) {
  rep(i, 1, n)
    vector<Edge>().swap(G[i]);
}
void add(int u, int v, int w) { G[u].pb({v, w}); G[v].pb({u, w}); }
struct Node {
  int u; ll d;
  bool operator < (const Node &b) const {
    return d > b.d;
  }
};
ll dis[N];
priority_queue<Node> q;
void Dijkstra(int s) {
  fill(dis, dis + n + 1, INF); dis[s] = 0; q.push({s, 0});
  while(q.size()) {
    int u = q.top().u; ll du = q.top().d; q.pop();
    if(dis[u] < du) continue ;
    for(auto &e : G[u]) {
      if(dis[e.v] > du + e.w) {
        dis[e.v] = du + e.w;
        q.push({e.v, dis[e.v]});
      }
    }
  }
}
int main() {
  // freopen("travel.in", "r", stdin);
  // freopen("travel.out", "w", stdout);
  int pos;
  scanf("%d%d%d", &n, &m, &pos);
  rep(i, 1, m)
    scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
  sort(e + 1, e + m + 1, [&](edge x, edge y) {
    return x.w < y.w;
  });
  rep(i, 0, n) rep(j, 0, n) dp[i][j] = INF;
  dp[0][1] = 0;
  rep(i, 1, n - 1)
    rep(j, 1, m) {
      dp[i][e[j].u] = min(dp[i][e[j].u], dp[i - 1][e[j].v] + e[j].w);
      dp[i][e[j].v] = min(dp[i][e[j].v], dp[i - 1][e[j].u] + e[j].w);
    }
  rep(i, 1, n) g[i] = dp[i][n];
  rep(i, 2, n) g[i] = min(g[i], g[i - 1]);
  rep(i, 1, m) {
    clean(n);
    rep(j, 1, m) {
      add(e[j].u, e[j].v, max(0, e[j].w - e[i].w));
    }
    Dijkstra(1);
    rep(j, 1, n)
      g[j] = min(g[j], dis[n] + 1ll * j * e[i].w);
  }
  printf("%lld\n", g[pos]);
  return 0;
}