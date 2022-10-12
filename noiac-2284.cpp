#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
using ll = long long;
using db = double;
namespace net {

const int N = 410, M = 1e4 + 10, INF = 1e9;
struct Edge {
  int v, c, f, w, nxt;
} e[M];
int hd[N], cur[N], ec, n, dis[N];
bool vis[N];
void init(int s) {
  n = s; fill(hd + 1, hd + n + 1, -1); ec = 0;
}
void add(int u, int v, int c, int w) {
  e[ec] = {v, c, 0, w, hd[u]}; hd[u] = ec ++;
  e[ec] = {u, 0, 0, -w, hd[v]}; hd[v] = ec ++;
}
bool spfa(int s, int t) {
  fill(dis + 1, dis + n + 1, -INF);
  queue<int> q; q.push(s); dis[s] = 0; vis[s] = 1;
  while(q.size()) {
    int u = q.front(); q.pop(); vis[u] = 0;
    for(int i = hd[u]; ~i; i = e[i].nxt) {
      Edge &p = e[i];
      if(p.f < p.c && dis[p.v] < dis[u] + p.w) {
        dis[p.v] = dis[u] + p.w;
        if(!vis[p.v]) { vis[p.v] = 1; q.push(p.v); }
      }
    }
  }
  return dis[t] > -INF;
}
int cost;
int dfs(const int t, int u, int a) {
  if(u == t || !a) return a;
  vis[u] = 1;
  int ans = 0, f = 0;
  for(int &i = cur[u]; ~i; i = e[i].nxt) {
    Edge &p = e[i];
    if(!vis[p.v] && dis[p.v] == dis[u] + p.w && (f = dfs(t, p.v, min(a, p.c - p.f))) > 0) {
      ans += f; p.f += f; e[i ^ 1].f -= f;
      cost += p.w * f;
      if(!(a -= f)) break ;
    }
  }
  vis[u] = 0;
  return ans;
}
int mcmf(int s, int t) {
  cost = 0;
  int ans = 0;
  while(spfa(s, t)) {
    copy(hd + 1, hd + n + 1, cur + 1);
    ans += dfs(t, s, INF);
  }
  return ans;
}

}
const int N = 180, W = 1e6;
int n, m, k, s, G[N][N], deg[N];
int main() {
  scanf("%d%d%d", &n, &m, &k);
  int x;
  rep(i, 1, n) scanf("%d", &x), s += x;
  net::init(2 * n + 3);
  rep(i, 1, m) {
    int x, y, w;
    scanf("%d%d%d", &x, &y, &w);
    if(!G[x][y]) ++ deg[y];
    G[x][y] = max(G[x][y], w);
  }
  rep(i, 1, n) net::add(2 * n + 1, i, 1, 0);
  rep(i, 1, n) rep(j, 1, n) if(G[i][j])
    net::add(i, n + j, 1, G[i][j]);
  rep(i, 1, n) {
    net::add(n + i, 2 * n + 2, 1, n + W);
    rep(j, 2, deg[i]) net::add(n + i, 2 * n + 3, 1, n - j + 1);
  }
  net::add(2 * n + 2, 2 * n + 3, 0, 0);
  auto pw = [&](double x) { return k^1 ? x * x : x; };
  db ans = 0;
  int id = net::ec;
  rep(i, 0, n - 1) {
    net::e[id-2].c = i;
    for(int j = 0; j < id; j ++) net::e[j].f = 0;
    int f = net::mcmf(2 * n + 1, 2 * n + 3);
    if(f >= i && net::e[id-2].f == i) {
      ans = max(ans, pw(net::cost - i*W + s) / (n - i));
    }
  }
  printf("%.11f\n", ans);
//  cerr << "time: " << clock() / (double) CLOCKS_PER_SEC << endl;
  return 0;
}