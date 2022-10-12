#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

const int N = 510;

int k, n, mod, f[N][N * 2], ans, inv[N * 2];

int main() {
   scanf("%d%d%d", &k, &n, &mod);
   int m = 2 * n + 1;
   rep(i, 0, m) f[0][i] = 1;
   rep(i, 1, n) rep(j, 1, m) {
      f[i][j] = (1ll * f[i - 1][j - 1] * j + f[i][j - 1]) % mod;
   }
   if(k <= m) {
      ans = f[n][k];
   } else {
      inv[1] = 1;
      rep(i, 2, m) inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
      rep(i, 1, m) {
         int y = 1;
         rep(j, i + 1, m) y = 1ll * y * (mod - inv[j - i]) % mod * (k - j) % mod;
         rep(j, 1, i - 1) y = 1ll * y * inv[i - j] % mod * (k - j) % mod;
         ans = (ans + 1ll * y * f[n][i]) % mod;
      }
   }
   rep(i, 1, n) ans = 1ll * ans * i % mod;
   printf("%d\n", ans);
   return 0;
}