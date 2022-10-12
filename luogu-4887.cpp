#include <bits/stdc++.h>
#define pb push_back
#define debug(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef long long ll;

const int N = 1e5 + 10;
const int M = 1 << 14;

struct node {
  int l, r, l2, id; ll ans;
  bool operator < (const node &b) const {
    return l2 == b.l2 ? r < b.r : l2 < b.l2;
  }
} c[N];
int n, m, mx = 1, k, sz, a[N], con[M];
ll f[N], g[N], ans[N];
vector<int> v;
struct node2 {
  int l, r, id, coef;
};
vector<node2> q[N];
int main() {
  scanf("%d%d%d", &n, &m, &k);
  if(k > 14) {
    rep(i, 1, m) puts("0");
    return 0;
  }
  sz = max(1, int(n / sqrt(m)));
  rep(i, 1, n) scanf("%d", a + i);
  for(int t = *max_element(a + 1, a + n + 1); mx <= t; mx <<= 1);
  for(int i = 0; i < mx; i ++) if(__builtin_popcount(i) == k) v.pb(i);
  rep(i, 1, n) {
    g[i] = g[i - 1] + con[a[i]];
    for(int x : v) con[a[i] ^ x] ++;
    f[i] = f[i - 1] + con[a[i]];
  }
  rep(i, 1, m) {
    scanf("%d%d", &c[i].l, &c[i].r);
    c[i].id = i;
    c[i].l2 = c[i].l / sz;
  }
  sort(c + 1, c + m + 1);
  int l = c[1].l, r = l - 1;
  rep(i, 1, m) {
    if(l < c[i].l) {
      // i in [l, c[i].l - 1] : - ( f(i, [1,r]) - f(i, [1,i-1]) )
      c[i].ans += g[c[i].l - 1] - g[l - 1];
      q[r].pb({l, c[i].l - 1, i, -1});;
    } else if(l > c[i].l) {
      // i in [c[i].l, l - 1] : + f(i, [1,r]) - f(i, [1,i-1])
      c[i].ans -= g[l - 1] - g[c[i].l - 1];
      q[r].pb({c[i].l, l - 1, i, 1});
    }
    l = c[i].l;
    if(r > c[i].r) {
      // i in [c[i].r + 1, r] : - ( f(i, [1,i]) - f(i, [1,l-1]) )
      c[i].ans -= f[r] - f[c[i].r];
      q[l - 1].pb({c[i].r + 1, r, i, 1});
    } else if(r < c[i].r) {
      // i in [r + 1, c[i].r] : f(i, [1,i]) - f(i, [1, l-1])
      c[i].ans += f[c[i].r] - f[r];
      q[l - 1].pb({r + 1, c[i].r, i, -1});
    }
    r = c[i].r;
  }
  fill(con, con + mx, 0);
  rep(i, 1, n) {
    for(int x : v) con[a[i] ^ x] ++;
    for(node2 &x : q[i]) {
      rep(k, x.l, x.r) c[x.id].ans += x.coef * con[a[k]];
    }
  }
  rep(i, 1, m) c[i].ans += c[i - 1].ans;
  rep(i, 1, m) ans[c[i].id] = c[i].ans - (k ? 0 : c[i].r - c[i].l + 1);
  rep(i, 1, m) printf("%lld\n", ans[i]);
  return 0;
}