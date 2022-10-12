#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
struct Edge { int v, w; };
vector<Edge> G[N];
int n, m, sz[N], f[N], tot, rt;
int top[N], son[N], d[N], dw[N], p[N];
bool vis[N];
void pdfs(int u, int fa = 0) {
  sz[u] = 1; d[u] = d[fa] + 1; p[u] = fa;
  for(Edge &e : G[u]) if(e.v != fa && !vis[e.v]) {
    dw[e.v] = dw[u] + e.w;
    pdfs(e.v, u);
    if(sz[e.v] > sz[son[u]]) son[u] = e.v;
  }
}
void pdfs2(int u, int t) {
  top[u] = t;
  if(son[u]) {
    pdfs2(son[u], t);
    for(Edge &e : G[u]) if(!top[e.v]) pdfs2(e.v, e.v);
  }
}
int LCA(int u, int v) {
  for(; top[u] != top[v]; u = p[top[u]])
    if(d[top[u]] < d[top[v]]) swap(u, v);
  return d[u] < d[v] ? u : v;
}
ll dis(int u, int v) { return dw[u] + dw[v] - 2 * dw[LCA(u, v)]; }
void findrt(int u, int fa = 0) {
  f[u] = sz[u] = 1;
  for(Edge &e : G[u]) if(e.v != fa && !vis[e.v]) {
    findrt(e.v, u);
    f[u] = max(f[u], sz[e.v]);
    sz[u] += sz[e.v];
  }
  f[u] = max(f[u], tot - sz[u]);
  if(!rt || f[rt] > f[u]) rt = u;
}
int pre[N];
ll sum[N], su[N], sf[N];
struct node { int v, rt; };
vector<node> out[N];
void build(int u) {
  vis[u] = 1;
  for(Edge &e : G[u]) if(!vis[e.v]) {
    tot = sz[e.v]; rt = 0; findrt(e.v);
    pre[rt] = u; out[u].pb({e.v, rt}); build(rt);
  }
}
void modify(int u, int val) {
  for(int v = u, la = 0; v; la = v, v = pre[v]) {
    ll d = dis(v, u);
    sum[v] += val; su[v] += val * d;
    if(la) sf[la] += val * d;
  }
}
ll calc(int u) {
  ll ans = 0;
  for(int v = u, la = 0; v; la = v, v = pre[v]) {
    ans += (sum[v] - sum[la]) * dis(v, u) + su[v] - sf[la];
  }
  return ans;
}
ll query(int u) {
  ll v = calc(u);
  for(node e : out[u])
    if(calc(e.v) < v)
      return query(e.rt);
  return v;
}
int main() {
  scanf("%d%d", &n, &m);
  int u, v, w;
  rep(i, 1, n - 1) {
    scanf("%d%d%d", &u, &v, &w);
    G[u].pb({v, w}); G[v].pb({u, w});
  }
  pdfs(1); pdfs2(1, 1);
  tot = n; rt = 0; findrt(1); int c = rt; build(rt);
  rep(i, 1, m) {
    scanf("%d%d", &u, &w);
    modify(u, w);
    printf("%lld\n", query(c));
  }
  return 0;
}