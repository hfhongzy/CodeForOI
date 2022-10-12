#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 5e5 + 10;
const int M = N * 128;
struct SMT {
  int tag[N * 4], w[N * 4];
  void init(int n) {
    fill(tag, tag + n * 4, -1);
  }
  void addtag(int u, int l, int r, int v) {
    tag[u] = v; w[u] = (r - l + 1) * v;
  }
  void up(int u) {
    w[u] = w[u << 1] + w[u << 1 | 1];
  }
  void down(int u, int l, int r) {
    if(~tag[u]) {
      int mid = (l + r) >> 1;
      addtag(u << 1, l, mid, tag[u]);
      addtag(u << 1 | 1, mid + 1, r, tag[u]);
      tag[u] = -1;
    }
  }
  void modify(int u, int l, int r, int ql, int qr, int v) {
    if(l == ql && r == qr) { addtag(u, l, r, v); return ; }
    int mid = (l + r) >>  1; down(u, l, r);
    if(qr <= mid) modify(u << 1, l, mid, ql, qr, v);
    else if(ql > mid) modify(u << 1 | 1, mid + 1, r, ql, qr, v);
    else {
      modify(u << 1, l, mid, ql, mid, v);
      modify(u << 1 | 1, mid + 1, r, mid + 1, qr, v);
    }
    up(u);
  }
  int query(int u, int l, int r, int ql, int qr) {
    if(l == ql && r == qr) return w[u];
    int mid = (l + r) >> 1; down(u, l, r);
    if(qr <= mid) return query(u << 1, l, mid, ql, qr);
    if(ql > mid) return query(u << 1 | 1, mid + 1, r, ql, qr);
    return query(u << 1, l, mid, ql, mid) + query(u << 1 | 1, mid + 1, r, mid + 1, qr);
  }
} seg;
struct node { int t, r, v; } a[M];
bool operator < (node a, node b) { return a.t < b.t; }
int n, m, ty, t, rt[N], id, ls[M], rs[M];
void build(int &u, int p, int l, int r, int ql, int qr, node x) {
  u = ++ id; ls[u] = ls[p]; rs[u] = rs[p]; a[u] = a[p];
  if(l == ql && r == qr) { a[u] = x; return ; }
  int mid = (l + r) >> 1;
  if(qr <= mid) build(ls[u], ls[p], l, mid, ql, qr, x);
  else if(ql > mid) build(rs[u], rs[p], mid + 1, r, ql, qr, x);
  else {
    build(ls[u], ls[p], l, mid, ql, mid, x);
    build(rs[u], rs[p], mid + 1, r, mid + 1, qr, x);
  }
}
node query(int u, int l, int r, int p) {
  if(!u) return {0, 0, 0};
  if(l == r) return a[u];
  int mid = (l + r) >> 1;
  return max(a[u], p <= mid ? query(ls[u], l, mid, p) : query(rs[u], mid + 1, r, p));
}
int main() {
  scanf("%d%d%d", &n, &m, &ty);
  seg.init(n);
  int op, l, r, x, lans = 0;
  rep(i, 1, m) {
    scanf("%d%d", &op, &l);
    l = (l + lans * ty) % n + 1;
    if(op != 2) {
      scanf("%d", &r);
      r = (r + lans * ty) % n + 1;
      if(r < l) swap(l, r);
    }
    if(op == 1) {
      printf("%d\n", lans = seg.query(1, 1, n, l, r));
    }
    if(op == 2) {
      int p = query(rt[t], 1, n, l).r;
      if(p) {
        node cur = query(rt[p - 1], 1, n, l);
        t ++; build(rt[t], rt[t - 1], 1, n, l, l, node{t, cur.r, cur.v});
        seg.modify(1, 1, n, l, l, cur.v);
      } else {
        t ++; build(rt[t], rt[t - 1], 1, n, l, l, node{t, 0, 0});
        seg.modify(1, 1, n, l, l, 0);
      }
    }
    if(op == 3) {
      scanf("%d", &x);
      t ++; build(rt[t], rt[t - 1], 1, n, l, r, node{t, t, x});
      seg.modify(1, 1, n, l, r, x);
    }
  }
  return 0;
}