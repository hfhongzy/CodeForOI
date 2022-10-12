#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int n, q, a[N];
namespace sub {
void main() {
  int op, l, r, x;
  rep(i, 1, q) {
    scanf("%d%d%d", &op, &l, &r);
    if(op == 1) {
      scanf("%d", &x);
      rep(j, l, r) a[j] &= x;
    }
    if(op == 2) {
      scanf("%d", &x);
      rep(j, l, r) a[j] |= x;
    }
    if(op == 3) {
      int ans = a[l];
      rep(j, l, r) ans = max(ans, a[j]);
      printf("%d\n", ans);
    }
  }
}
}
namespace sol {
#define ls u << 1, l, mid
#define rs u << 1 | 1, mid + 1, r
template<class T>
struct SMT {
  T w[N * 4], tag[N * 4];
  void addtag(int u, T v) { tag[u] += v; w[u] += v; }
  void up(int u) { w[u] = max(w[u << 1], w[u << 1 | 1]); }
  void down(int u) {
    if(tag[u]) {
      addtag(u << 1, tag[u]);
      addtag(u << 1 | 1, tag[u]);
      tag[u] = 0;
    }
  }
  void build(int u, int l, int r) {
    if(l == r) { w[u] = a[l]; return ; }
    int mid = (l + r) >> 1;
    build(ls); build(rs); up(u);
  }
  void modify(int u, int l, int r, int ql, int qr, T v) {
    if(l == ql && r == qr) { addtag(u, v); return ; }
    int mid = (l + r) >> 1; down(u);
    if(qr <= mid) modify(ls, ql, qr, v);
    else if(ql > mid) modify(rs, ql, qr, v);
    else { modify(ls, ql, mid, v); modify(rs, mid + 1, qr, v); }
    up(u);
  }
  T query(int u, int l, int r, int ql, int qr) {
    if(l == ql && r == qr) return w[u];
    int mid = (l + r) >> 1; down(u);
    if(qr <= mid) return query(ls, ql, qr);
    if(ql > mid) return query(rs, ql, qr);
    return max(query(ls, ql, mid), query(rs, mid + 1, qr));
  }
};
#undef ls
#undef rs
SMT<int> seg;
struct node {
  int l, r, v;
  bool operator < (const node &b) const {
    return l < b.l;
  }
};
typedef set<node>::iterator odt;
set<node> S[22];
int b[N];
odt split(int w, int x) { //[l, x - 1][x, r]
  odt it = -- S[w].lower_bound({x + 1, 0});
  node cur = *it;
  if(cur.l == x) return it;
  S[w].erase(cur);
  S[w].insert(node{cur.l, x - 1, cur.v});
  return S[w].insert(node{x, cur.r, cur.v}).first;
}
void cover(int w, int l, int r, int v) {
  odt itr = split(w, r + 1);
  odt itl = split(w, l);
  for(odt it = itl; it != itr; it ++) if(it->v != v) {
    seg.modify(1, 1, n, it->l, it->r, v ? (1 << w) : -(1 << w));
  }
  S[w].erase(itl, itr);
  S[w].insert(node{l, r, v});
}
void main() {
  seg.build(1, 1, n);
  rep(i, 0, 20) {
    S[i].insert(node{0, 0, -1});
    S[i].insert(node{n + 1, n + 1, -1});
    int st = 0;
    b[0] = b[n + 1] = -1;
    rep(j, 1, n) b[j] = a[j] >> i & 1;
    rep(j, 1, n) {
      if(b[j] != b[j - 1]) st = j;
      if(b[j + 1] != b[j]) {
        S[i].insert(node{st, j, b[j]});
      }
    }
  }
  int op, l, r, x;
  rep(T, 1, q) {
    scanf("%d%d%d", &op, &l, &r);
    if(op == 1) {
      scanf("%d", &x);
      rep(i, 0, 20)
        if(!(x >> i & 1))
          cover(i, l, r, 0);
    }
    if(op == 2) {
      scanf("%d", &x);
      rep(i, 0, 20)
        if(x >> i & 1)
          cover(i, l, r, 1);
    }
    if(op == 3) {
      printf("%d\n", seg.query(1, 1, n, l, r));
    }
  }
}
}
int main() {
  scanf("%d%d", &n, &q);
  rep(i, 1, n) scanf("%d", a + i);
  if(max(n, q) <= 5000) {
    sub::main(); return 0;
  }
  sol::main();
  return 0;
}