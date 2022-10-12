#include <algorithm>
#include <cstdio>
using namespace std;
typedef pair<int, int> pii;
const int mod = 1e9 + 9, N = 4010;
int n, k, a[N], b[N], dp[N][N], fav[N], fac[N];
pii c[N];
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
      if(b & 1) ans = 1ll * ans * a % mod;
   return ans;
}
int C(int n, int m) {
   return 1ll * fac[n] * fav[m] % mod * fav[n - m] % mod;
}
int main() {
   scanf("%d%d", &n, &k);
   if((n + k) & 1) { puts("0"); return 0; }
   fac[0] = 1;
   for(int i = 1; i <= n; i ++) fac[i] = 1ll * fac[i - 1] * i % mod;
   fav[n] = qpow(fac[n], mod - 2);
   for(int i = n; i >= 1; i --) fav[i - 1] = 1ll * fav[i] * i % mod;
   k = (n + k) >> 1;
   for(int i = 1; i <= n; i ++) scanf("%d", a + i), c[i] = pii(a[i], 1);
   for(int i = 1; i <= n; i ++) scanf("%d", b + i), c[n + i] = pii(b[i], 2);
   sort(c + 1, c + n + n + 1);
   dp[0][0] = 1; int c2 = 0;
   for(int i = 1; i <= n + n; i ++) {
      c2 += c[i - 1].second == 2;
      int c1 = i - 1 - c2;
      for(int j = min(c1, c2); j >= 0; j --) dp[i][j] = dp[i - 1][j];
      if(c[i].second == 1) {
         for(int j = min(c1, c2); j >= 0; j --) if(dp[i - 1][j]) {
            if(c2 - j > 0) {
               (dp[i][j + 1] += 1ll * dp[i - 1][j] * (c2 - j) % mod) %= mod;
            }
         }
      }
   }
   int ans = 0;
   for(int i = k; i <= n; i ++) {
      int tmp = 1ll * C(i, k) * dp[n + n][i] % mod * fac[n - i] % mod;
      if((i - k) & 1) (ans += mod - tmp) %= mod;
      else (ans += tmp) %= mod;
   }
   printf("%d\n", ans);
   return 0;
}
//x:[a>b] x == n + k / 2
/*
dp[i][j]表示对于sort的数组，前i个我选了j对，方案数
f : 选了k对, g : 恰k对
f(k) = \sum_{i = k}^n C(i, k) g(i)
g(k) = \sum_{i = k}^n (-1)^{i - k} C(i, k) f(i)
*/