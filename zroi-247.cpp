#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
template<class T>
struct BIT {
  vector<T> c;
  int n;
  BIT(int sz) { c.resize(1 + (n = sz)); }
  void add(int x, T y) {
    for(; x <= n; x += x & (-x))
      c[x] += y;
  }
  T qry(int x) {
    T ans = 0;
    for(; x >= 1; x &= x - 1)
      ans += c[x];
    return ans;
  }
};
template<class T>
struct SMT {
  T w[N * 4], tag[N * 4];
  void addtag(int u, T v) { tag[u] += v; w[u] += v; }
  void up(int u) { w[u] = min(w[u << 1], w[u << 1 | 1]); }
  void down(int u) {
    if(tag[u]) {
      addtag(u << 1, tag[u]);
      addtag(u << 1 | 1, tag[u]);
      tag[u] = 0;
    }
  }
  void build(int u, int l, int r) {
    if(l == r) { w[u] = l - 1; return ; }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    up(u);
  }
  void modify(int u, int l, int r, int ql, int qr, T v) {
    if(l == ql && r == qr) { addtag(u, v); return ; }
    int mid = (l + r) >> 1; down(u);
    if(qr <= mid) modify(u << 1, l, mid, ql, qr, v);
    else if(ql > mid) modify(u << 1 | 1, mid + 1, r, ql, qr, v);
    else {
      modify(u << 1, l, mid, ql, mid, v);
      modify(u << 1 | 1, mid + 1, r, mid + 1, qr, v);
    }
    up(u);
  }
};
SMT<int> seg;
int n, a[N], pos[N];
ll ans;
int main() {
  scanf("%d", &n);
  BIT<int> bit(n >> 1);
  rep(i, 1, n / 2) {
    scanf("%d", a + i);
    pos[a[i]] = i;
    ans += i - 1 - bit.qry(a[i] >> 1);
    bit.add(a[i] >> 1, 1);
  }
  seg.build(1, 1, n / 2 + 1);
  for(int i = 3; i <= n; i += 2) {
    seg.modify(1, 1, n / 2 + 1, 1, pos[i - 1], 1);
    seg.modify(1, 1, n / 2 + 1, pos[i - 1] + 1, n / 2 + 1, -1);
    ans += seg.w[1];
  }
  printf("%lld\n", ans);
  return 0;
}