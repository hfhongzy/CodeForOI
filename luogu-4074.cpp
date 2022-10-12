#include <bits/stdc++.h>
#define fs first
#define sc second
#define pb push_back
#define debug(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, m, q, v[N], w[N], c[N];

int d[N], sz[N], son[N], fa[N];
int idx, dfn[N], top[N], pos[N];
vector<int> G[N]; 
void dfs(int u, int p = 0) {
  sz[u] = 1; fa[u] = p; d[u] = d[p] + 1;
  for(int v : G[u]) if(v ^ p) {
    dfs(v, u); sz[u] += sz[v];
    if(sz[v] > sz[son[u]]) son[u] = v;
  }
}
void dfs2(int u, int t) {
  top[u] = t; dfn[u] = ++ idx; pos[idx] = u;
  if(!son[u]) return ;
  dfs2(son[u], t);
  for(int v : G[u]) if(!dfn[v]) dfs2(v, v);
}
int LCA(int u, int v) {
  for(; top[u] ^ top[v]; u = fa[top[u]])
    if(d[top[u]] < d[top[v]]) swap(u, v);
  return dfn[u] < dfn[v] ? u : v;
}

int bel[N], st[N], siz, tot, B;
void dfs3(int u, int fa = 0) {
  int t = siz;
  for(int v : G[u]) if(v != fa) {
    dfs3(v, u);
    if(siz - t >= B) {
      tot ++;
      while(t < siz) bel[st[siz --]] = tot;
    }
  }
  st[++ siz] = u;
}
void block() {
  dfs3(1);
  if(!tot) ++ tot;
  while(siz) bel[st[siz --]] = tot;
}

struct Modify { int t, p, v; };
struct Query { int t, u, v; };
vector<Modify> vm;
vector<Query> vq;

int cnt[N];
bool vis[N];
ll cur, ans[N];
void flip(int x) {
  if(vis[x]) {
    cur -= (ll)w[cnt[c[x]] --] * v[c[x]];
    vis[x] = 0;
  } else {
    cur += (ll)w[++ cnt[c[x]]] * v[c[x]];
    vis[x] = 1;
  }
}
void change(int u, int v) {
  while(u != v) {
    // assert(u && v);
    if(d[u] < d[v]) swap(u, v);
    flip(u); u = fa[u];
  }
}
void modify(Modify &v) {
  if(vis[v.p]) {
    flip(v.p); swap(c[v.p], v.v); flip(v.p); return ;
  }
  swap(c[v.p], v.v);
}
int main() {
  scanf("%d%d%d", &n, &m, &q); B = max(1, int(pow(n, 2.0 / 3)));
  rep(i, 1, m) scanf("%d", v + i);
  rep(i, 1, n) scanf("%d", w + i);
  int op, x, y;
  rep(i, 1, n - 1) {
    scanf("%d%d", &x, &y); G[x].pb(y); G[y].pb(x);
  }
  rep(i, 1, n) scanf("%d", c + i);
  dfs(1); dfs2(1, 1); block();
  rep(i, 1, q) {
    scanf("%d%d%d", &op, &x, &y);
    if(op == 0) vm.pb({i, x, y});
    if(op == 1) {
      if(dfn[x] > dfn[y]) swap(x, y);
      vq.pb({i, x, y});
    }
  }
  sort(vq.begin(), vq.end(), [&](Query x, Query y) {
    return bel[x.u] == bel[y.u] ? (bel[x.v] == bel[y.v] ? x.t < y.t : bel[x.v] < bel[y.v]) : bel[x.u] < bel[y.u];
  });
  vm.pb({q + 1, 0, 0});
  int u = 1, v = 1, t = 0;
  for(auto x : vq) {
    change(u, x.u); change(v, x.v);
    u = x.u; v = x.v;
    while(vm[t].t <= x.t) modify(vm[t ++]);
    while(t && vm[t - 1].t > x.t) modify(vm[-- t]);
    int z = LCA(u, v);
    flip(z); ans[x.t] = cur; flip(z);
  }
  rep(i, 1, q) if(ans[i]) printf("%lld\n", ans[i]);
  return 0;
}
/*
4 2 1
5 6
1 1 1 1
1 2
1 3
3 4
1 1 2 2
1 1 4
*/