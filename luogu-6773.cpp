#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
using ll = long long;
const int mod = 998244353;
const int N = 5e5 + 10;
const int M = N * 32;
void upd(int &x, int y) { (x += y) >= mod ? x -= mod : 0; }
int add(int x, int y) { return upd(x, y), x; }
int n, m, h, up[N], d[N], rt[N];
vector<int> G[N];
void dfs(int u, int fa = 0) {
  d[u] = d[fa] + 1;
  for(int v : G[u]) if(v != fa) dfs(v, u);
}
int s[M], id, ls[M], rs[M], tag[M];
void insert(int &u, int l, int r, int p) {
  u = ++ id; tag[u] = s[u] = 1;
  if(l == r) return ;
  int mid = (l + r) >> 1;
  if(p <= mid) insert(ls[u], l, mid, p);
  else insert(rs[u], mid + 1, r, p);
}
void addtag(int u, int t) {
  tag[u] = (ll)tag[u] * t % mod;
  s[u] = (ll)s[u] * t % mod;
}
void down(int u) {
  if(tag[u] ^ 1) {
    if(ls[u])
      addtag(ls[u], tag[u]);
    if(rs[u])
      addtag(rs[u], tag[u]);
    tag[u] = 1;
  }
}
void pup(int u) {
  s[u] = add(s[ls[u]], s[rs[u]]);
}
int query(int u, int l, int r) {
  while(u && l < r) {
    down(u);
    // printf("[%d %d]!\n", l, r);
    r = (l + r) >> 1;
    u = ls[u];
  }
  return s[u];
}
int query(int u, int l, int r, int ql, int qr) {
  if(l == ql && r == qr) return s[u];
  int mid = (l + r) >> 1; down(u);
  if(qr <= mid) return query(ls[u], l, mid, ql, qr);
  if(ql > mid) return query(rs[u], mid + 1, r, ql, qr);
  return add(query(ls[u], l, mid, ql, mid), query(rs[u], mid + 1, r, mid + 1, qr));
}
void print(int u, int l, int r) {
  printf("s[%d, %d] = %d\n", l, r, s[u]);
  if(l == r) return ;
  down(u);
  print(ls[u], l, (l + r) >> 1);
  print(rs[u], ((l + r) >> 1) + 1, r);
}
int Merge(int u, int v, int l, int r, int sA, int sB) {
  if(!u && !v) return 0;
  if(!v) { addtag(u, sB); return u; }
  if(!u) { addtag(v, sA); return v; }
  if(l == r) {
    s[u] = ((ll)sB * s[u] + (ll)(sA + s[u]) * s[v]) % mod;
    return u;
  }
  down(u); down(v);
  int mid = (l + r) >> 1;
  rs[u] = Merge(rs[u], rs[v], mid + 1, r, add(sA, s[ls[u]]), add(sB, s[ls[v]]));
  ls[u] = Merge(ls[u], ls[v], l, mid, sA, sB);
  pup(u);
  return u;
}
void dfs2(int u, int fa = 0) {
  insert(rt[u], 0, h, up[u]);
  for(int v : G[u]) if(v != fa) {
    dfs2(v, u);
    // printf("merge %d [fa = %d]\n", v, u);
    rt[u] = Merge(rt[u], rt[v], 0, h, 0, query(rt[v], 0, h, 0, d[u]));
    // print(rt[u], 0, h);
  }
}
int main() {
  scanf("%d", &n);
  int u, v;
  rep(i, 1, n - 1) {
    scanf("%d%d", &u, &v);
    G[u].pb(v); G[v].pb(u);
  }
  dfs(1);
  scanf("%d", &m);
  rep(i, 1, m) {
    scanf("%d%d", &u, &v);
    up[v] = max(up[v], d[u]);
  }
  rep(i, 1, n) h = max(h, d[i]);
  dfs2(1);
  printf("%d\n", query(rt[1], 0, h));
  return 0;
}