#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
using ll = long long;
const int N = 5e4 + 10;
const int M = 1e5 + 10;
int n, m, d[N], fa[N], fw[N];
int seq[N], len, pos[N], id;
int lg[M], st[16][M];
ll dep[N];
vector<int> G[N];
int lower(int x, int y) {
  return d[x] < d[y] ? x : y;
}
void build() {
  lg[1] = 0;
  rep(i, 2, len) lg[i] = lg[i >> 1] + 1;
  rep(i, 1, len) st[0][i] = seq[i];
  rep(k, 1, lg[len]) rep(i, 1, len - (1 << k) + 1)
    st[k][i] = lower(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
}
int lca(int u, int v) {
  u = pos[u]; v = pos[v];
  if(u > v) swap(u, v);
  int k = lg[v - u + 1];
  return lower(st[k][u], st[k][v - (1 << k) + 1]);
}
ll dist(int u, int v) {
  return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}
struct path {
  int u, v; ll d;
  bool operator < (const path &b) const {
    return d == b.d ? u < b.u : d < b.d;
  }
} pa[N * 4];
path operator + (path a, path b) {
  if(!a.u) return b;
  if(!b.u) return a;
  path ans = max(a, b);
  ans = max(ans, {a.u, b.u, dist(a.u, b.u)});
  ans = max(ans, {a.v, b.u, dist(a.v, b.u)});
  ans = max(ans, {a.u, b.v, dist(a.u, b.v)});
  ans = max(ans, {a.v, b.v, dist(a.v, b.v)});
  return ans;
}
#define ls u << 1, l, mid
#define rs u << 1 | 1, mid + 1, r
void build(int u, int l, int r) {
  if(l == r)
    return ;
  int mid = (l + r) >> 1;
  build(ls); build(rs);
  pa[u] = pa[u << 1] + pa[u << 1 | 1];
}
void del(int u, int l, int r, int p) {
  if(l == r) { pa[u] = {0, 0, 0}; return ; }
  int mid = (l + r) >> 1;
  p <= mid ? del(ls, p) : del(rs, p);
  pa[u] = pa[u << 1] + pa[u << 1 | 1];
}
path query(int u, int l, int r, int ql, int qr) {
  if(l == ql && r == qr) return pa[u];
  int mid = (l + r) >> 1;
  if(qr <= mid) return query(ls, ql, qr);
  if(ql > mid) return query(rs, ql, qr);
  return query(ls, ql, mid) + query(rs, mid + 1, qr);
}
#undef ls
#undef rs
struct node {
  ll w; int u;
};
vector<int> va[N];
void dfs(int u) {
  seq[++ len] = u; pos[u] = len;
  for(int v : G[u]) {
    dep[v] = dep[u] + fw[v];
    dfs(v);
    seq[++ len] = u;
  }
}
int main() {
  int test;
  scanf("%d", &test);
  rep(T, 1, test) {
    scanf("%d", &n);
    rep(i, 1, n) G[i].clear();
    int u, v, w;
    rep(i, 1, n - 1) {
      scanf("%d%d", &u, &v);
      fa[v] = u; G[u].pb(v);
      scanf("%d", fw + v);
    }
    len = id = 0;
    dfs(1);
    build();
    rep(i, 1, m) {
      scanf("%d%d%d", &u, &v, &w);
    }
  }
  return 0;
}