#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 2e5 + 10, M = 452, mod = 1e9 + 7;
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
      if(b & 1) ans = 1ll * ans * a % mod;
   return ans;
}
int n, k, ans, fac[N], fav[N], f[M][N]; 
int C(int n, int m) {
   return n < m ? 0 : 1ll * fac[n] * fav[m] % mod * fav[n - m] % mod;
}
void binom(int n) {
   fac[0] = 1;
   for(int i = 1; i <= n; i ++) fac[i] = 1ll * fac[i - 1] * i % mod;
   fav[n] = qpow(fac[n], mod - 2);
   for(int i = n; i >= 1; i --) fav[i - 1] = 1ll * fav[i] * i % mod;
}
int main() {
   scanf("%d%d", &n, &k); binom(n + k);
   f[0][0] = 1;
   int m = 1;
   while(m < n && m * (m + 1) / 2 <= k) m ++;
   rep(i, 1, m) {
      rep(j, 1, k) {
         if(j >= i) f[i][j] = f[i - 1][j - i]; // ... 1
         if(j >= i) (f[i][j] += f[i][j - i]) %= mod; // ... >= 2
         if(j >= n + 1) (f[i][j] += mod - f[i - 1][j - n - 1]) %= mod; // n + 1 ... 2
      }
   }
   rep(j, 0, k) {
      int cur = 0;
      rep(i, 0, m) if(f[i][j]) {
         if(!(i & 1)) (cur += f[i][j]) %= mod;
         else (cur += mod - f[i][j]) %= mod;
      }
      (ans += 1ll * cur * C(k - j + n - 1, n - 1) % mod) %= mod;
   }
   printf("%d\n", ans);
   return 0;
}