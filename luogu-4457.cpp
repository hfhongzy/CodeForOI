#include <algorithm>
#include <cstdio>
using namespace std;
const int mod = 1e9 + 7, N = 1520;
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
      if(b & 1) ans = 1ll * ans * a % mod;
   return ans;
}
int inv(int x) { return qpow(x, mod - 2); }
int n, m, k, x, p, Ck[N], g[N], Inv[N], ty[N], a[N][N];
void gauss(int n) {
   for(int i = n; i >= 1; i --) {
      int j = i;
      for(int k = i; k >= 1; k --) if(a[k][i]) { j = k; break ; }
      if(j != i) {
         for(int k = 1; k <= i; k ++) swap(a[i][k], a[j][k]);
         swap(a[i][n + 1], a[j][n + 1]);
      }
      int y = inv(a[i][i]);
      for(j = i - 1; j >= 1; j --) {
         int u = 1ll * a[j][i] * y % mod;
         if(u == 0) continue ;
         for(int k = 1; k <= i; k ++) {
            (a[j][k] += mod - 1ll * u * a[i][k] % mod) %= mod;
         }
         (a[j][n + 1] += mod - 1ll * u * a[i][n + 1] % mod) %= mod;
      }
      ty[i] = y;
   }
   for(int i = 1; i <= n; i ++) {
      int y = ty[i];
      for(int j = i - 1; j >= 1; j --) {
         (a[i][n + 1] += mod - 1ll * a[i][j] * a[j][n + 1] % mod) %= mod;
      }
      a[i][n + 1] = 1ll * a[i][n + 1] * y % mod;
   }
}
int main() {
   Inv[1] = 1;
   for(int i = 2; i < N; i ++)
      Inv[i] = 1ll * (mod - mod / i) * Inv[mod % i] % mod;
   int T; scanf("%d", &T);
   while(T --) {
      scanf("%d%d%d%d", &n, &x, &m, &k); p = inv(m + 1);
      if(!k || (k == 1 && !m)) {
         puts("-1"); continue ;
      } 
      Ck[0] = 1;
      for(int i = 0; i < n && i < k; i ++) {
         Ck[i + 1] = 1ll * Ck[i] * Inv[i + 1] % mod * (k - i) % mod;
      }
      for(int i = 0, tp = 1; i <= n; i ++) {
         g[i] = 1ll * Ck[i] * tp % mod * qpow(mod + 1 - p, k - i) % mod;
         tp = 1ll * tp * p % mod;
      }
      for(int i = k + 1; i <= n; i ++) g[i] = 0;
      for(int i = 1; i <= n; i ++) {]
         fill(a[i], a[i] + n + 2, 0);
         a[i][n + 1] = a[i][i] = mod - 1;
         if(i == n) {
            for(int j = 1; j <= n; j ++) {
               (a[i][j] += g[n - j]) %= mod;
            }
         } else {
            a[i][i + 1] = 1ll * p * g[0] % mod;
            for(int j = 1; j <= i; j ++) {
               int t = (1ll * p * g[i - j + 1] + (mod + 1ll - p) * g[i - j]) % mod;
               (a[i][j] += t) %= mod;
            }
         }
      }
      gauss(n);
      printf("%d\n", a[x][n + 1]);
   }
   return 0;
}