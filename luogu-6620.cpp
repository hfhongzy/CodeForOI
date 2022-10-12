#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1010;
int n, ans, x, mod, m, a[N], S[N][N], pw[N], pw2[N];
int qpow(int a, int b) {
   int ans = 1; a %= mod;
   for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
      if(b & 1) ans = 1ll * ans * a % mod;
   return ans;
}
int main() {
   scanf("%d%d%d%d", &n, &x, &mod, &m);
   for(int i = 0; i <= m; i ++) scanf("%d", a + i);
   S[0][0] = pw[0] = 1;
   int x1 = qpow(x + 1, mod - 2);
   for(int i = 1; i <= m; i ++) {
      pw[i] = 1ll * pw[i - 1] * x % mod;
      pw2[i] = 1ll * pw2[i - 1] * x1 % mod;
      for(int j = 1; j <= i; j ++) {
         S[i][j] = (S[i - 1][j - 1] + 1ll * S[i - 1][j] * j) % mod;
      }
   }
   int up = min(m, n);
   pw2[up] = qpow(x + 1, n - up);
   for(int i = up - 1; i >= 0; i --)
      pw2[i] = pw2[i + 1] * (x + 1ll) % mod;
   int xn = qpow(x + 1, n);
   for(int i = 0; i <= m; i ++) {
      int d = 0, tp = 1;
      for(int j = 0; j <= min(i, n); j ++) {
         (d += 1ll * tp * S[i][j] % mod * pw[j] % mod * pw2[j] % mod) %= mod;
         tp = 1ll * tp * (n - j) % mod;
      }
      (ans += 1ll * d * a[i] % mod) %= mod;
   }
   printf("%d\n", ans);
   return 0;
}