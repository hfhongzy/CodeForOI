#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, m, a[N], g[N];
ll s[N], f[N];
ll func(int u, int x) {
   return f[u] + (s[u] - 1) * (s[u] - 1) - 2 * s[x] * (s[u] - 1);
}
ll cross(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3) { //13 dot 12
   return (x3 - x1) * (y2 - y1) - (x2 - x1) * (y3 - y1);
}
ll cross(int x, int y, int z) {
   return cross(
      2 * (s[x] - 1), f[x] + (s[x] - 1) * (s[x] - 1),
      2 * (s[y] - 1), f[y] + (s[y] - 1) * (s[y] - 1),
      2 * (s[z] - 1), f[z] + (s[z] - 1) * (s[z] - 1)
   );
}
ll calc(ll k) {
   static int q[N];
   int ql = 0, qr = 0;
   f[0] = 0; q[qr ++] = 0;
   rep(i, 1, n) {
      while(qr - ql > 1 && func(q[ql], i) > func(q[ql + 1], i)) ql ++;
      f[i] = f[q[ql]] + (s[i] - s[q[ql]] + 1) * (s[i] - s[q[ql]] + 1) + k;
      // f[i] = 1e9;
      // rep(j, 0, i - 1) if(f[j] + (s[i] - s[j] + 1) * (s[i] - s[j] + 1) + k < f[i]) {
      //    f[i] = f[j] + (s[i] - s[j] + 1) * (s[i] - s[j] + 1) + k; g[i] = g[j] + 1;
      // }
      g[i] = g[q[ql]] + 1;
      while(qr - ql > 1 && cross(q[qr - 2], q[qr - 1], i) > 0) qr --;
      q[qr ++] = i;
   }
   // fprintf(stderr, "f, g = %lld, %d\n", f[n], g[n]);
   return g[n];
}
int main() {
   scanf("%d%d", &n, &m);
   rep(i, 1, n) {
      scanf("%d", a + i);
      s[i] = s[i - 1] + a[i];
   }
   ll l = 0, r = 1e18, mid, k = 0, ans;
   while(l <= r) {
      mid = (l + r) >> 1;
      if(calc(mid) <= m) {
         r = (k = mid) - 1; ans = f[n];
      } else {
         l = mid + 1;
      }
   }
   // printf("ans = %lld, k = %lld\n", ans, k);
   printf("%lld\n", ans - k * m);
   return 0;
}