#include <bits/stdc++.h>
#define debug(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;
template<class T>
struct BIT {
  vector<T> c, d;
  int n; T s;
  BIT(int sz) {
    s = 0;
    c.resize(1 + (n = sz));
    d.resize(1 + n);
  }
  void add(int x, T z) {
    s += z;
    T z2 = z * x;
    for(; x <= n; x += x & (-x)) {
      c[x] += z; d[x] += z2;
    }
  }
  void add(int x, int y, T z) {
    if(x > 1) add(x - 1, -z);
    add(y, z);
  }
  T qry(int x) {
    T ans = s;
    for(int u = x; u >= 1; u &= u - 1) {
      ans -= c[u];
    }
    ans *= x;
    for(; x >= 1; x &= x - 1) {
      ans += d[x];
    }
    return ans;
  }
  T qry(int x, int y) {
    return qry(y) - qry(x - 1);
  }
};
struct node {
  int l, r, x;
  bool operator < (const node &b) const {
    return l < b.l;
  }
};
set<node> S;
typedef set<node>::iterator odt;
int n, m, q, a[N];
ll ans[N];
odt split(int x) { //[l,x-1], [x,r]
  odt it = -- S.lower_bound({x + 1, x + 1, 0});
  node t = *it;
  if(t.l == x) return it;
  S.erase(it);
  S.insert({t.l, x - 1, t.x});
  return S.insert({x, t.r, t.x}).first;
}
int main() {
  scanf("%d%d%d", &n, &m, &q);
  S.insert({0, 0, 0}); S.insert({n + 1, n + 1, 0});
  rep(i, 1, n) scanf("%d", a + i), S.insert({i, i, a[i]});
  BIT<ll> bit(n);
  int op, l, r, x;
  rep(i, 1, q) {
    scanf("%d%d%d%d", &op, &l, &r, &x);
    if(op == 1) {
      auto itR = split(r + 1);
      auto itL = split(l);
      for(auto it = itL; it != itR; it ++) {
        ans[it->x] += bit.qry(it->l, it->r);
      }
      S.erase(itL, itR);
      ans[x] -= bit.qry(l, r);
      S.insert({l, r, x});
    }
    if(op == 2) {
      bit.add(l, r, x);
    }
  }
  for(auto it = S.begin(); it != S.end(); it ++) {
    if(!it->x) continue ;
    ans[it->x] += bit.qry(it->l, it->r);
  }
  rep(i, 1, m) printf("%lld\n", ans[i]);
  return 0;
}