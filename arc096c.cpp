#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 3005;
int n, mod, S[N][N], C[N][N];
int qpow(int a, int b, int mo = mod) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = 1ll * a * a % mo)
      if(b & 1) ans = 1ll * ans * a % mo;
   return ans;
}
void init(int n) {
   S[0][0] = C[0][0] = 1;
   for(int i = 1; i <= n; i ++) {
      C[i][0] = 1;
      for(int j = 1; j <= i; j ++) {
         S[i][j] = (1ll * j * S[i - 1][j] + S[i - 1][j - 1]) % mod;
         C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
      }
   }
}
int main() {
   scanf("%d%d", &n, &mod); init(n + 1);
   int ans = 0;
   for(int i = 0; i <= n; i ++) {
      int cur = 0, t1 = qpow(2, n - i), t2 = 1;
      for(int j = 0; j <= i; j ++, t2 = 1ll * t2 * t1 % mod) {
         (cur += 1ll * S[i + 1][j + 1] * t2 % mod) %= mod;
      }
      cur = 1ll * cur * C[n][i] % mod * qpow(2, qpow(2, n - i, mod - 1)) % mod;
      if(i & 1) (ans += mod - cur) %= mod;
      else (ans += cur) %= mod;
   }
   printf("%d\n", ans);
   return 0;
}