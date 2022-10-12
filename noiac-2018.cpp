#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int N = 3010;
int n, x, y, p, q, f[N][N], c[N][N], ans[N], pw[N], qw[N], iqw[N], inv[N];
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
int main() {
   scanf("%d%d%d%d", &n, &x, &y, &q); p = 1ll * x * qpow(y, mod - 2) % mod;
   pw[0] = qw[0] = inv[1] = 1;
   rep(i, 1, n) pw[i] = 1ll * pw[i - 1] * p % mod;
   rep(i, 1, n) qw[i] = qw[i - 1] * (mod + 1ll - p) % mod;
   rep(i, 0, n) iqw[i] = qpow(qw[i], mod - 2);
   rep(i, 2, n) inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
   rep(i, 0, n) {
      c[i][i] = c[i][0] = 1;
      rep(j, 1, i - 1) {
         c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
      }
   }
   f[0][n] = 1;
   rep(i, 1, n) {
      rep(j, 1, n) {
         rep(k, j + 1, n) if(f[i - 1][k]) {
            (f[i][j] += c[k - 2][j - 1] * (k - 1ll) % mod * inv[k] % mod * qw[k - j - 1] % mod * f[i - 1][k] % mod) %= mod;
         }
         f[i][j] = 1ll * f[i][j] * pw[j] % mod;
      }
   }
   rep(i, 1, n) {
      rep(j, 1, n) {
         (ans[i] += 1ll * f[i - 1][j] * inv[j] % mod) %= mod;
      }
   }
   while(q --) {
      scanf("%d", &x);
      printf("%d\n", ans[x]);
   }
   return 0;
}