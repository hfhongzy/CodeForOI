#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
#define debug(x) fprintf(stderr, "%s = %d\n", #x, x);
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
const ll INF = 1ll << 60;
ll h[N], w[N], s[N], dp[N], x[N], y[N];
int n, q[N], a[N], t[N], o[N];
bool cmpa(int u, int v) { return x[u] < x[v]; }
bool cmpb(int u, int v) { return - h[u] < - h[v]; }
ll det(ll x1, ll y1, ll x2, ll y2) { return x1 * y2 - x2 * y1; }
void solve(int l, int r) {
   if(l == r) {
      if(l > 1) dp[l] += s[l - 1] + h[l] * h[l];
      // printf("%lld!\n", dp[l]);
      x[l] = - 2 * h[l];
      y[l] = dp[l] + h[l] * h[l] - s[l];
      a[l] = l;
      return ;
   }
   int mid = (l + r) >> 1, p = l;
   rep(i, l, r) if(q[i] <= mid) t[p ++] = q[i];
   rep(i, l, r) if(q[i] > mid) t[p ++] = q[i];
   rep(i, l, r) q[i] = t[i];

   solve(l, mid);

   int ql = 0, qr = 0;
   rep(i, l, mid) {
      while(qr - ql > 1 && det(x[a[i]] - x[o[qr - 2]], y[a[i]] - y[o[qr - 2]], x[a[i]] - x[o[qr - 1]], y[a[i]] - y[o[qr - 1]]) <= 0) {
         qr --;
      }
      o[qr ++] = a[i];
   }
   rep(i, mid + 1, r) {
      while(qr - ql > 1 && y[o[ql + 1]] - y[o[ql]] <= - h[q[i]] * (x[o[ql + 1]] - x[o[ql]])) {
         ql ++;
      }
      dp[q[i]] = min(dp[q[i]], h[q[i]] * x[o[ql]] + y[o[ql]]);
   }

   solve(mid + 1, r);

   int p1 = l, p2 = mid + 1;
   rep(i, l, r) {
      if(p1 <= mid && (p2 > r || cmpa(a[p1], a[p2]))) {
         t[i] = a[p1 ++];
      } else {
         t[i] = a[p2 ++];
      }
   }
   rep(i, l, r) a[i] = t[i];

   p1 = l; p2 = mid + 1;
   rep(i, l, r) {
      if(p1 <= mid && (p2 > r || cmpb(q[p1], q[p2]))) {
         t[i] = q[p1 ++];
      } else {
         t[i] = q[p2 ++];
      }
   }
   rep(i, l, r) q[i] = t[i];
}
int main() {
   scanf("%d", &n);
   rep(i, 1, n) scanf("%lld", h + i);
   rep(i, 1, n) scanf("%lld", w + i), s[i] = s[i - 1] + w[i];
   rep(i, 1, n) q[i] = i;
   sort(q + 1, q + n + 1, cmpb);
   rep(i, 1, n) dp[i] = i == 1 ? 0 : INF;
   solve(1, n);
   printf("%lld\n", dp[n]);
   return 0;
}