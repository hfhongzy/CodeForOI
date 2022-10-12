#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 210, mod = 998244353;
int n, q, a[N], f[N][N], inv[N];
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
      if(b & 1) ans = 1ll * ans * a % mod;
   return ans;
}
int main() {
   scanf("%d", &n);
   for(int i = 1; i <= n; i ++) { scanf("%d", a + i); f[i][a[i]] = 1; }
   inv[1] = 1;
   for(int i = 2; i <= n; i ++)
      inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
   scanf("%d", &q);
   while(q --) {
      int op, k; scanf("%d%d", &op, &k);
      if(op == 0) {
         int p, pt; scanf("%d%d", &p, &pt);
         p = 1ll * p * qpow(pt, mod - 2) % mod;
         static int g[N];
         for(int i = 0; i <= a[k]; i ++) {
            g[i] = (1ll * f[k][i] * (i == 0 ? 1 : mod + 1 - p) % mod + 1ll * f[k][i + 1] * p % mod) % mod;
         }
         copy(g, g + a[k] + 1, f[k]);
      }
      if(op == 1) {
         static int seq[N], g[N][N], fu[N];
         for(int i = 1; i <= k; i ++) scanf("%d", seq + i);
         for(int i = 0; i <= k; i ++) fill(g[i], g[i] + k + 2, 0);
         g[0][0] = 1;
         for(int i = 1; i <= k; i ++) {
            int u = seq[i];
            for(int j = 0; j <= i; j ++) {
               g[i][j] = 1ll * g[i - 1][j] * f[u][0] % mod;
               if(j) (g[i][j] += 1ll * g[i - 1][j - 1] * (mod + 1 - f[u][0]) % mod) %= mod;
            }
         }
         for(int i = 1; i <= k; i ++) {
            int u = seq[i], t = qpow(f[u][0], mod - 2);
            if(!f[u][0]) {
               for(int j = 0; j < k; j ++) {
                  fu[j] = g[k][j + 1];
               }
            } else {
               fu[0] = 1ll * g[k][0] * t % mod;
               for(int j = 1; j < k; j ++) {
                  fu[j] = (g[k][j] - 1ll * fu[j - 1] * (mod + 1 - f[u][0]) % mod + mod) * t % mod;
               }
            }
            int res = 0;
            for(int j = 0; j < k; j ++) {
               fu[j] = 1ll * fu[j] * (mod + 1 - f[u][0]) % mod;
               (res += 1ll * fu[j] * inv[j + 1] % mod) %= mod;
            }
            printf("%d ", res);
         }
         putchar('\n');
      }
   }
   for(int i = 1; i <= n; i ++) {
      int res = 0;
      for(int j = 1; j <= a[i]; j ++) {
         (res += 1ll * f[i][j] * j % mod) %= mod;
      }
      printf("%d ", res);
   }
   return 0;
}
