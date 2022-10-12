#include <bits/stdc++.h>
#define fs first
#define sc second
#define pb push_back
#define mp make_pair
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
struct Edge { int v, w; };
vector<Edge> G[N];
int n, q, m, sz[N], a[N], f[N], tot, rt;
int top[N], son[N], d[N], dw[N], p[N], vis[N];
void pdfs(int u, int fa = 0) {
  sz[u] = 1; d[u] = d[fa] + 1; p[u] = fa;
  for(Edge &e : G[u]) if(e.v != fa) {
    dw[e.v] = dw[u] + e.w; pdfs(e.v, u);
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
int pre[N], lim, tim;
vector<pair<int, ll>> vec[N], vf[N];
void get(int u, vector<pair<int, ll>> &num, int d, int fa = 0) {
  num.pb(mp(a[u], d));
  for(Edge &e : G[u]) if(e.v != fa && (~lim ? vis[e.v] >= lim : !vis[e.v])) {
    get(e.v, num, d + e.w, u);
  }
}
struct tup {
  int v, rt, w;
};
void build(int u) {
  // printf("pre%d = %d\n", u, pre[u]);
  vis[u] = ++ tim; lim = -1; get(u, vec[u], 0);
  vector<tup> son;
  for(Edge &e : G[u]) if(!vis[e.v]) {
    tot = sz[e.v]; rt = 0; findrt(e.v);
    pre[rt] = u; son.pb({e.v, rt, e.w}); build(rt);
  }
  lim = vis[u];
  for(auto x : son) {
    get(x.v, vf[x.rt], x.w, u);
  }
}
struct Node {
  int cnt; ll sum;
  Node operator - (Node x) {
    return Node{cnt - x.cnt, sum - x.sum};
  }
};
Node ask(vector<pair<int, ll>> &num, int r) {
  if(!num.size() || r < num[0].fs) return Node{0, 0};
  auto it = lower_bound(num.begin(), num.end(), pair<int, ll>(r + 1, -1ll));
  it --;
  return Node{static_cast<int>(it - num.begin() + 1), it->sc};
}
Node ask(vector<pair<int, ll>> &num, int l, int r) {
  return ask(num, r) - ask(num, l - 1);
}
ll calc(int u, int l, int r) {
  ll ans = 0;
  for(int v = u, la = 0; v; la = v, v = pre[v]) {
    ll d = dis(v, u);
    Node tmp = ask(vec[v], l, r) - ask(vf[la], l, r);
    ans += tmp.cnt * d + tmp.sum;
  }
  return ans;
}
int main() {
  scanf("%d%d%d", &n, &q, &m);
  rep(i, 1, n) scanf("%d", a + i);
  int u, v, w, l, r;
  rep(i, 1, n - 1) {
    scanf("%d%d%d", &u, &v, &w);
    G[u].pb({v, w}); G[v].pb({u, w});
  }
  pdfs(1); pdfs2(1, 1);
  tot = n; rt = 0; findrt(1); build(rt);
  rep(u, 1, n) {
    sort(vec[u].begin(), vec[u].end(), [&](auto x, auto y) { return x.fs < y.fs; });
    sort(vf[u].begin(), vf[u].end(), [&](auto x, auto y) { return x.fs < y.fs; });
    for(int i = 1; i < int(vec[u].size()); i ++)
      vec[u][i].sc += vec[u][i - 1].sc;
    for(int i = 1; i < int(vf[u].size()); i ++)
      vf[u][i].sc += vf[u][i - 1].sc;
    // printf("vf, vec = %lu, %lu\n", vf[u].size(), vec[u].size());
  }
  ll lans = 0;
  rep(i, 1, q) {
    scanf("%d%d%d", &u, &l, &r);
    l = (l + lans) % m; r = (r + lans) % m;
    if(l > r) swap(l, r);
    printf("%lld\n", lans = calc(u, l, r));
  }
  return 0;
}

