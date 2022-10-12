#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 2e5 + 10;
int n, m, sz[N], f[N], tot, rt;
vector<int> G[N];
int top[N], son[N], d[N], p[N];
bool vis[N];
void pdfs(int u, int fa = 0) {
  sz[u] = 1; d[u] = d[fa] + 1; p[u] = fa;
  for(int v : G[u]) if(v != fa && !vis[v]) {
    pdfs(v, u);
    if(sz[v] > sz[son[u]]) son[u] = v;
  }
}
void pdfs2(int u, int t) {
  top[u] = t;
  if(son[u]) {
    pdfs2(son[u], t);
    for(int v : G[u]) if(!top[v]) pdfs2(v, v);
  }
}
int LCA(int u, int v) {
  for(; top[u] != top[v]; u = p[top[u]])
    if(d[top[u]] < d[top[v]]) swap(u, v);
  return d[u] < d[v] ? u : v;
}
int dis(int u, int v) { return d[u] + d[v] - 2 * d[LCA(u, v)]; }
void dfs0(int u, int fa = 0) {
  f[u] = sz[u] = 1;
  for(int v : G[u]) if(v != fa && !vis[v]) {
    dfs0(v, u);
    f[u] = max(f[u], sz[v]);
    sz[u] += sz[v];
  }
  f[u] = max(f[u], tot - sz[u]);
  if(!rt || f[rt] > f[u]) rt = u;
}
struct ds {
  vector<int> bit;
  int n, s;
  void init(int m) { //[0, m]
    n = m + 1; s = 0; bit.resize(n + 1);
  }
  void add(int x, int y) { //[0, x] += y
    s += y;
    for(x += 2; x <= n; x += x & (-x))
      bit[x] -= y;
  }
  int qry(int x) { //query x
    // if(x > n - 1) return 0;
    int z = s;
    for(x ++; x >= 1; x &= x - 1)
      z += bit[x];
    return z;
  }
} au[N], af[N];
int mx[N], pre[N];
int far(int u, int fa = 0) {
  int ans = 0;
  for(int v : G[u]) if(v != fa && !vis[v])
    ans = max(ans, 1 + far(v, u));
  return ans;
}
void build(int u) {
  vis[u] = 1; mx[u] = far(u);
  au[u].init(mx[u]);
  if(pre[u]) af[u].init(mx[pre[u]]);
  for(int v : G[u]) if(!vis[v]) {
    tot = sz[v]; rt = 0; dfs0(v);
    pre[rt] = u; build(rt);
  }
}
void modify(int u, int x, int val) {
  for(int v = u, la = 0; v; la = v, v = pre[v]) {
    int d = dis(v, u);
    if(x - d >= 0) {
      au[v].add(min(x - d, mx[v]), val);
      if(la) af[la].add(min(x - d, mx[v]), -val);
    }
  }
}
int query(int u) {
  int ans = 0;
  for(int v = u, la = 0; v; la = v, v = pre[v]) {
    int d = dis(v, u);
    ans += au[v].qry(d);
    if(la) ans += af[la].qry(d);
  }
  return ans;
}
int main() {
  scanf("%d%d", &n, &m);
  int u, v;
  rep(i, 1, n - 1) {
    scanf("%d%d", &u, &v);
    G[u].pb(v); G[v].pb(u);
  }
  pdfs(1); pdfs2(1, 1);
  tot = n; rt = 0; dfs0(1); build(rt);
  char op[16];
  rep(i, 1, m) {
    scanf("%s", op);
    if(*op == 'Q') {
      int u; scanf("%d", &u);
      printf("%d\n", query(u));
    }
    if(*op == 'M') {
      int u, d, w;
      scanf("%d%d%d", &u, &d, &w);
      modify(u, d, w);
    }
  }
  return 0;
}