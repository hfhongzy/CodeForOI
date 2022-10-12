#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 210;
const int INF = 1 << 30;
int n, m, a[N][N], a0[N][N], b[N][N];

namespace net {

struct Edge {
  int v, c, f, nxt;
} e[N * N * 2];
int hd[N], cur[N], n, ec, d[N], s, t;
void clr(int sz, int ss, int tt) {
  s = ss; t = tt; n = sz; fill(hd, hd + n + 1, -1); ec = 0;
}
void add(int u, int v, int c) {
  e[ec] = {v, c, 0, hd[u]}; hd[u] = ec ++;
  e[ec] = {u, 0, 0, hd[v]}; hd[v] = ec ++;
}
bool bfs() {
  fill(d, d + n + 1, -1);
  queue<int> q; q.push(t); d[t] = INF;
  while(q.size()) {
    int u = q.front(); q.pop();
    for(int i = hd[u]; ~i; i = e[i].nxt) {
      int v = e[i].v;
      if(e[i ^ 1].f < e[i ^ 1].c && !~d[v]) {
        d[v] = d[u] - 1;
        q.push(v);
        if(v == s) return ~d[s];
      }
    }
  }
  return ~d[s];
}
int dfs(int u, int a) {
  if(u == t || a == 0) return a;
  int ans = 0, f;
  for(int &i = cur[u]; ~i; i = e[i].nxt) {
    Edge &e = net::e[i];
    if(d[e.v] == d[u] + 1 && (f = dfs(e.v, min(a, e.c - e.f))) > 0) {
      net::e[i].f += f; net::e[i ^ 1].f -= f; ans += f;
      if(!(a -= f)) break ;
    }
  }
  return ans;
}
void dinic() {
  while(bfs()) {
    copy(hd, hd + n + 1, cur);
    (void)dfs(s, INF);
  }
}

}
int main() {
  scanf("%d%d", &n, &m);
  rep(i, 1, n) rep(j, 1, m)
    scanf("%d", a[i] + j), a0[i][j] = (a[i][j] + m - 1) / m;
  rep(j, 1, m) {
    net::clr(2 * n + 2, 2 * n + 1, 2 * n + 2);
    rep(i, 1, n) net::add(2 * n + 1, i, 1);
    rep(i, 1, n) net::add(n + i, 2 * n + 2, 1);
    rep(i, 1, n) rep(k, 1, m) if(a0[i][k]) net::add(i, n + a0[i][k], 1);
    net::dinic();
    rep(i, 1, n) {
      int col = 0;
      for(int e = net::hd[i]; ~e; e = net::e[e].nxt) {
        if(net::e[e].f && net::e[e].v != 2 * n + 1) {
          col = net::e[e].v - n;
          break ;
        }
      }
      rep(j, 1, m) if(a0[i][j] == col) {
        a0[i][j] = 0; col = a[i][j]; break ;
      }
      b[i][j] = col;
    }
  }
  
  rep(i, 1, n) rep(j, 1, m) printf("%d%c", b[i][j], " \n"[j == m]);
  rep(j, 1, m) {
    static int ord[N];
    rep(i, 1, n) ord[i] = b[i][j];
    sort(ord + 1, ord + n + 1);
    rep(i, 1, n) b[i][j] = ord[i];
  }
  rep(i, 1, n) rep(j, 1, m) printf("%d%c", b[i][j], " \n"[j == m]);
  return 0;
}