#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j, _k = k; i <= _k; ++ i)
#define per(i, j, k) for(int i = j, _k = k; i >= _k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 10, K = 105;
const ll INF = -2e18;
int n, k, m, pos[N], cnt[K], a[N];
ll f[N], g[N], s[N], t1[N], t2[N], ans;
ll calc(int x) {
   return f[x - 1] - (x - 1ll) * (x - 1ll) - s[x - 1];
}
ll cross(int x, int y, int z) { //(x, y) det (x, z)
   ll x1 = y - x, y1 = calc(y) - calc(x);
   ll x2 = z - x, y2 = calc(z) - calc(x);
   return x1 * y2 - x2 * y1;
}
int main() {
   scanf("%d%d", &n, &k);
   rep(i, 1, n) {
      scanf("%d", a + i);
      if(!a[i]) { pos[++ m] = i; continue ; }
      rep(j, a[i] + 1, k) ans += cnt[j];
      cnt[a[i]] ++;
   }
   if(!m) { printf("%lld\n", ans); return 0; }
   static int q[N], ql, qr;
   fill(f + 1, f + m + 1, INF);
   f[0] = 0;
   per(j, k, 1) {
      rep(i, 1, n) t1[i] = t1[i - 1] + (0 < a[i] && a[i] < j);
      rep(i, 1, n) t2[i] = t2[i - 1] + (0 < a[i] && a[i] > j);
      rep(i, 1, m) s[i] = s[i - 1] + t1[n] - t1[pos[i]] + t2[pos[i] - 1];
      ql = qr = 0;
      rep(i, 1, m) {
         while(qr - ql >= 2 && cross(q[qr - 2], q[qr - 1], i) >= 0) qr --;
         q[qr ++] = i;
         while(qr - ql >= 2 && calc(q[ql]) - calc(q[ql + 1]) < - (ll) i * (q[ql] - q[ql + 1])) ql ++;
         int u = q[ql];
         g[i] = f[u - 1] + (i - u + 1ll) * (u - 1ll) + s[i] - s[u - 1];
      }
      rep(i, 1, m) f[i] = max(f[i], g[i]);
   }
   ans += f[m];
   printf("%lld\n", ans);
   return 0;
}