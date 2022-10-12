#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2510;
namespace net {

const int N = 3010, M = 4e5 + 10, INF = 998244353;
struct Edge {
  int v, c, f, nxt;
} e[M];
int ec, hd[N], n, s, t, vis[N];
void init(int _n) { n = t = _n; s = n - 1; fill(hd + 1, hd + n + 1, -1); fill(vis + 1, vis + n + 1, -1); ec = 0; }
void add(int u, int v, int c) {
  e[ec] = (Edge) {v, c, 0, hd[u]}; hd[u] = ec ++;
  e[ec] = (Edge) {u, 0, 0, hd[v]}; hd[v] = ec ++;
}
int dis[N], cur[N];
bool bfs() {
  fill(dis + 1, dis + n + 1, -1);
  queue<int> q; q.push(s); dis[s] = 0;
  while(q.size()) {
    int u = q.front(); q.pop();
    for(int i = hd[u]; ~ i; i = e[i].nxt) {
      int v = e[i].v;
      if(e[i].f < e[i].c && -1 == dis[v]) {
        dis[v] = dis[u] + 1; q.push(v);
      }
    }
  }
  return ~ dis[t];
}
int dfs(int u, int a) {
  if(u == t || a == 0) return a;
  int ans = 0, f;
  for(int &i = cur[u]; ~ i; i = e[i].nxt) {
    int v = e[i].v;
    if(dis[v] == dis[u] + 1 && (f = dfs(v, min(a, e[i].c - e[i].f))) > 0) {
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
bool dfs2(int u, int lim) { //right u
  if(~vis[u]) return vis[u];
  if(u > lim) {
    int mat = -1;
    for(int i = hd[u]; ~i; i = e[i].nxt) {
      int v = e[i].v;
      if(v == s || v == t) continue ;
      if(e[i].f) { mat = v; break; }
    }
    return vis[u] = ~mat ? dfs2(mat, lim) : 1;
  }
  bool mark = 0;
  for(int i = hd[u]; ~i; i = e[i].nxt) {
    int v = e[i].v;
    if(v == s || v == t || e[i].f) continue ;
    mark |= dfs2(v, lim);
    if(mark) break ;
  }
  return vis[u] = mark;
}

}
char s[N], t[N];
vector<int> G[N];
int n, m, op[N], f[N], ID[N];
bool dp[N][101], oc[101];
void cpy(int u, int v) { for(int x : G[v]) G[u].pb(x); G[v].clear(); }
void dfs(int u) {
  if(!G[u].size()) {
    f[u] = 1; dp[u][op[u]] = 1; return ;
  }
  for(int v : G[u]) dfs(v);
  f[u] = 1;
  fill(oc + 1, oc + m + 1, 0);
  int c = 0;
  for(int v : G[u]) {
    if(G[v].size()) ID[v] = ++ c;
    else {
      if(oc[op[v]]) f[u] --;
      oc[op[v]] = 1;
      dp[u][op[v]] = 1;
    }
    f[u] += f[v];
  }
  net::init(m + c + 2);
  rep(i, 1, m) if(oc[i]) {
    net::add(net::s, i, 1);
    for(int v : G[u]) if(ID[v] && dp[v][i])
      net::add(i, m + ID[v], 1);
  }
  for(int v : G[u]) if(ID[v])
    net::add(m + ID[v], net::t, 1);
  f[u] -= net::dinic();
  for(int v : G[u]) if(ID[v] && net::dfs2(m + ID[v], m)) {
    rep(i, 1, m) dp[u][i] |= dp[v][i];
  }
  // printf("f%d = %d\n", u, f[u]);
}
int main() {
  freopen("expr.in", "r", stdin);
  freopen("expr.out", "w", stdout);
  scanf("%s", s + 1);
  n = strlen(s + 1);
  // cerr << "n = " << n << endl;
  copy(s + 1, s + n + 1, t + 1);
  sort(t + 1, t + n + 1);
  m = unique(t + 1, t + n + 1) - t - 1;
  // cerr << "m = " << m << endl;
  static int st[N];
  int top = 0;
  rep(i, 1, n) {
    int ch = lower_bound(t + 1, t + m + 1, s[i]) - t;
    if(!('a' <= t[ch] && t[ch] <= 'z')) {
      op[i] = ch;
      int u = st[top], v = st[top - 1];
      if(op[u] == ch) cpy(i, u); else G[i].pb(u);
      if(op[v] == ch) cpy(i, v); else G[i].pb(v);
      st[-- top] = i;
    } else {
      op[i] = ch;
      st[++ top] = i;
    }
  }
  // assert(top == 1);
  dfs(st[1]);
  printf("%d\n", f[st[1]]);
  return 0;
}