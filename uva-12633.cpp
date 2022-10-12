#include <algorithm>
#include <complex>
#include <cstdio>
using namespace std;
typedef long long ll;
typedef complex<double> comp;
const int N = 2e5 + 10;
const double pi = acos(-1);
int n, m, k, lim, r[N];
bool ua[N], ub[N], uc[N];
comp a[N], b[N];
void fft(comp *a, int type) {
   for(int i = 0; i < lim; i ++)
      if(i < r[i]) swap(a[i], a[r[i]]);
   for(int i = 1; i < lim; i <<= 1) {
      comp x(cos(pi / i), type * sin(pi / i));
      for(int j = 0; j < lim; j += i << 1) {
         comp y(1, 0);
         for(int k = 0; k < i; k ++, y *= x) {
            comp p = a[j + k], q = y * a[j + k + i];
            a[j + k] = p + q; a[j + k + i] = p - q;
         }
      }
   }
}
int main() {
   int t, ca = 0; scanf("%d", &t);
   while(t --) {
      scanf("%d%d%d", &n, &m, &k);
      fill(ua, ua + n + 1, 1); fill(ub, ub + m + 1, 1); fill(uc, uc + n + m, 0);
      ua[0] = ub[0] = 0; ll ans = 0;
      for(int i = 1; i <= k; i ++) {
         int x, y; scanf("%d%d", &x, &y);
         ua[x] = ub[y] = 0; uc[x - y + m] = 1;
      }
      ll sx = 0, sy = 0;
      for(int i = 1; i <= n; i ++) if(!ua[i]) sx ++;
      for(int i = 1; i <= m; i ++) if(!ub[i]) sy ++;
      ans = sx * m + sy * n - sx * sy;
      int l = 0;
      for(lim = 1; lim <= n + m; lim <<= 1) ++ l;
      for(int i = 0; i < lim; i ++)
         r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
      for(int i = 0; i < lim; i ++) a[i] = comp((int) (i <= n && ua[i]), 0);
      for(int i = 0; i < lim; i ++) b[i] = comp((int) (i <= m && ub[m - i]), 0);
      fft(a, 1); fft(b, 1);
      for(int i = 0; i < lim; i ++) a[i] *= b[i];
      fft(a, -1);
      for(int i = 1; i <= n + m - 1; i ++) if(uc[i]) {
         ans += (ll) ( (a[i].real() + 0.4) / lim );
      }
      printf("Case %d: %lld\n", ++ ca, 1ll * n * m - ans);
   }
}