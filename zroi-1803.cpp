#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e4 + 5;
const ll INF = 1ll << 60;
ll sqr(ll x) { return x * x; }
int n, k, a[N], p[N], t[N];
ll f[N], g[N], h[N];
bool neg_cross(int x, int y, int z) {
  ll x1 = a[y + 1] - a[x + 1], y1 = h[y] - h[x];
  ll x2 = a[z + 1] - a[x + 1], y2 = h[z] - h[x];
  return (long double)x1 * y2 <= (long double)x2 * y1;
}
ll calc(int x, int h) {
  return g[x] + sqr(h - a[x + 1]);
}
void split(int l, int mid, int r) {
  static int ord[N];
  int p1 = l, p2 = mid + 1;
  rep(i, l, r) {
    if(t[i] <= mid) ord[p1 ++] = t[i];
    else ord[p2 ++] = t[i];
  }
  copy(ord + l, ord + r + 1, t + l);
}
void solve(int l, int r) {
  if(l == r) { p[l] = l; return ; }
  int mid = (l + r) >> 1;
  split(l, mid, r);
  solve(l, mid);
  static int q[N];
  int ql = 0, qr = 0;
  rep(i, l, mid) if(g[p[i]] < INF) {
    while(qr - ql > 1 && neg_cross(q[qr - 2], q[qr - 1], p[i])) qr --;
    q[qr ++] = p[i];
  }
  rep(i, mid + 1, r) {
    int u = t[i];
    while(qr - ql > 1 && calc(q[ql], a[u]) >= calc(q[ql + 1], a[u])) ql ++;
    if(qr - ql >= 1) {
      f[u] = min(f[u], calc(q[ql], a[u]));
    }
  }
  solve(mid + 1, r);
  inplace_merge(p + l, p + mid + 1, p + r + 1, [&](int x, int y) {
    return a[x + 1] < a[y + 1] || (a[x + 1] == a[y + 1] && g[x] > g[y]);
  });
}
int main() {
  scanf("%d%d", &n, &k);
  rep(i, 1, n) scanf("%d", a + i);
  rep(i, 1, n) f[i] = sqr(a[i] - a[1]);
  static int ord[N];
  rep(i, 1, n) t[i] = i;
  sort(t + 1, t + n + 1, [&](int x, int y) {
    return a[x] < a[y];
  });
  rep(i, 1, n) ord[i] = t[i];
  rep(i, 2, k) {
    rep(j, 1, n) {
      g[j] = f[j]; f[j] = INF; h[j] = g[j] + sqr(a[j + 1]);
    }
    copy(ord + 1, ord + n + 1, t + 1);
    solve(1, n);
  }
  printf("%lld\n", f[n]);
  return 0;
}