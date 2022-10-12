#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

const int N = 2e5 + 10;
const int M = 4 * N;
const int INF = 2147483640;

namespace Net {

struct Edge { int v, c, f, nxt; } e[M];
int n, s, t, hd[N], p;
void init(int _n, int _s, int _t) {
  n = _n; s = _s; t = _t;
  fill(hd + 1, hd + n + 1, -1); p = 0;
}
void add(int u, int v, int c) {
  e[p] = (Edge) {v, c, 0, hd[u]}; hd[u] = p ++;
  e[p] = (Edge) {u, 0, 0, hd[v]}; hd[v] = p ++;
}
queue<int> q;
int d[N], cur[N];
bool bfs() {
  fill(d + 1, d + n + 1, -1); q.push(s); d[s] = 0;
  while(!q.empty()) {
    int u = q.front(); q.pop();
    for(int i = hd[u]; ~ i; i = e[i].nxt) {
      int v = e[i].v; 
      if(d[v] == -1 && e[i].c > e[i].f) {
        d[v] = d[u] + 1; q.push(v);
      }
    }
  }
  return ~ d[t];
}
int dfs(int u, int a) {
  if(u == t || a == 0) return a;
  int ans = 0, f;
  for(int &i = cur[u]; ~ i; i = e[i].nxt) {
    int v = e[i].v;
    if(d[u] + 1 == d[v] && e[i].c > e[i].f && (f = dfs(v, min(a, e[i].c - e[i].f))) > 0) {
      ans += f; e[i].f += f; e[i ^ 1].f -= f;
      if((a -= f) == 0) break ;
    }
  }
  return ans;
}
int dinic() {
  int ans = 0;
  while(bfs()) {
    copy(hd + 1, hd + n + 1, cur + 1);
    ans += dfs(s, INF);
  }
  return ans;
}

}
using Net::hd;
using Net::e;
int n, mat[N * 2];
int main() {
  scanf("%d", &n);
  Net::init(2 * n + 1, 2 * n, 2 * n + 1);
  rep(i, 1, n) Net::add(Net::s, i, 1);
  rep(i, 1, n - 1) Net::add(n + i, Net::t, 1);
  rep(i, 1, n - 1) {
    int sz, u;
    scanf("%d", &sz);
    while(sz --) {
      scanf("%d", &u);
      Net::add(u, n + i, 1);
    }
  }
  int sz = Net::dinic();
  if(sz < n - 1) { puts("-1"); return 0; }
  int rt = 0;
  for(int i = hd[Net::s]; ~i; i = e[i].nxt)
    if(e[i].f == 0) { rt = e[i].v; break ; }
  rep(i, 1, n) if(rt != i) for(int j = hd[i]; ~j; j = e[j].nxt) if(e[j].f == 1) {
    mat[e[j].v] = i; break ;
  }
  queue<int> q; q.push(rt);
  vector< pair<int, int> > edge(n);
  vector<bool> vis(n + 1); vis[rt] = 1;
  int cc = 0;
  while(q.size()) {
    int u = q.front(); q.pop();
    for(int i = hd[u]; ~ i; i = e[i].nxt) {
      int v = e[i].v;
      if(v < 2 * n && !vis[mat[v]]) {
        cc ++;
        edge[v - n - 1] = {u, mat[v]};
        vis[mat[v]] = 1;
        q.push(mat[v]);
      }
    }
  }
  if(cc < n - 1) {
    puts("-1"); return 0;
  }
  for(int i = 0; i < n - 1; i ++) {
    printf("%d %d\n", edge[i].first, edge[i].second);
  }
  return 0;
}