#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
using ll = long long;
const int N = 2e5 + 10;
const int M = N * 51;
int n, m, rt[N], c, a[N];
int id, ls[M], rs[M];
ll sz[M];
void build(int &u, int l, int r) {
  u = ++ id;
  if(l == r) { sz[u] = a[l]; return ; }
  int mid = (l + r) >> 1;
  build(ls[u], l, mid);
  build(rs[u], mid + 1, r);
  sz[u] = sz[ls[u]] + sz[rs[u]];
}
void insert(int &u, int l, int r, int p, int v) {
  if(!u) u = ++ id;
  sz[u] += v;
  if(l == r) return ;
  int mid = (l + r) >> 1;
  if(p <= mid) insert(ls[u], l, mid, p, v);
  else insert(rs[u], mid + 1, r, p, v);
}
void merge(int &u, int v, int l, int r) {
  if(!u || !v) { u |= v; return ; }
  sz[u] += sz[v];
  if(l == r) return ;
  int mid = (l + r) >> 1;
  merge(ls[u], ls[v], l, mid);
  merge(rs[u], rs[v], mid + 1, r);
}
void split(int &u, int &v, int l, int r, int p) {
  if(r <= p) { v = 0; return ; }
  if(l > p) { v = u; u = 0; return ; }
  v = ++ id;
  int mid = (l + r) >> 1;
  split(ls[u], ls[v], l, mid, p);
  split(rs[u], rs[v], mid + 1, r, p);
  sz[u] = sz[ls[u]] + sz[rs[u]];
  sz[v] = sz[ls[v]] + sz[rs[v]];
}
int ql, qr;
ll query(int u, int l, int r) {
  if(!u || l > qr || r < ql) return 0;
  if(ql <= l && r <= qr) return sz[u];
  int mid = (l + r) >> 1;
  return query(ls[u], l, mid) + query(rs[u], mid + 1, r);
}
int kth(int u, int l, int r, ll k) {
  if(l == r) return k <= sz[u] ? l : -1;
  int mid = (l + r) >> 1;
  if(sz[ls[u]] >= k) return kth(ls[u], l, mid, k);
  return kth(rs[u], mid + 1, r, k - sz[ls[u]]);
}
int main() {
  scanf("%d%d", &n, &m);
  rep(i, 1, n) scanf("%d", a + i);
  build(rt[c = 1], 1, n);
  int op, p, x, y, r1, r2;
  rep(T, 1, m) {
    scanf("%d%d", &op, &p);
    if(op == 0) {
      scanf("%d%d", &x, &y);
      c ++;
      split(rt[p], r1, 1, n, x - 1);
      split(r1, r2, 1, n, y);
      rt[c] = r1;
      merge(rt[p], r2, 1, n);
    }
    if(op == 1) {
      scanf("%d", &x);
      merge(rt[p], rt[x], 1, n);
      rt[x] = 0;
    }
    if(op == 2) {
      scanf("%d%d", &x, &y);
      insert(rt[p], 1, n, y, x);
    }
    if(op == 3) {
      scanf("%d%d", &x, &y); ql = x; qr = y;
      printf("%lld\n", query(rt[p], 1, n));
    }
    if(op == 4) {
      ll k;
      scanf("%lld", &k);
      printf("%d\n", kth(rt[p], 1, n, k));
    }
  }
  return 0;
}