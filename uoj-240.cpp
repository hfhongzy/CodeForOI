#include <bits/stdc++.h>
#define debug(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
const ll sqr(ll x) { return x * x; }
struct node {
   int l, r;
} a[N];
int n, m, k, d[N];
struct point {
   ll x, y;
   point operator - (point b) { return point {x - b.x, y - b.y}; }
   friend ll det(point a, point b) { return a.x * b.y - a.y * b.x; }
} p[N];
ll dp[N];
ll calc(int u, int v) {
   return dp[u] + sqr(a[v].r - a[u + 1].l + 1);
}
void check(ll v) {
   static int q[N];
   int ql = 0, qr = 0;
   q[qr ++] = 0; p[0] = {a[1].l, sqr(a[1].l - 1ll)};
   rep(i, 1, n) {
      while(qr - ql > 1 && calc(q[ql], i) > calc(q[ql + 1], i)) ql ++;
      dp[i] = calc(q[ql], i) + v; d[i] = d[q[ql]] + 1;
      if(i == n) break ;
      dp[i] -= sqr(max(0, a[i].r - a[i + 1].l + 1));
      p[i] = {a[i + 1].l, sqr(a[i + 1].l - 1ll) + dp[i]};
      while(qr - ql > 1 && det(p[q[qr - 1]] - p[q[qr - 2]], p[i] - p[q[qr - 2]]) <= 0) qr --;
      q[qr ++] = i;
   }
}
ll take_photos(int nn, int mm, int kk, vector<int> vr, vector<int> vc) {
   n = nn; m = mm; k = kk;
   int x, y;
   rep(i, 0, n - 1) {
      x = vr[i] + 1; y = vc[i] + 1;
      if(x > y) swap(x, y);
      a[i + 1] = {x, y};
   }
   sort(a + 1, a + n + 1, [&](node x, node y) { return x.l < y.l || (x.l == y.l && x.r > y.r); });
   int sz = 0;
   rep(i, 1, n) {
      if(a[i].r > a[sz].r) {
         a[++ sz] = a[i];
      }
   }
   n = sz; k = min(k, n);
   ll l = 0, r = 1ll << 42, ans = 0;
   while(l <= r) {
      ll mid = (l + r) >> 1; check(mid);
      if(d[n] <= k) {
         r = mid - 1;
         ans = dp[n] - k * mid;
      } else {
         l = mid + 1;
      }
   }
   return ans;
}