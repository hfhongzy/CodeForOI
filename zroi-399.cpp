#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 3010, mod = 998244353;

int n, d[N], a[N], f[N], c[N][N], pw[N];
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}

int main() {
   scanf("%d", &n);
   rep(i, 1, n) scanf("%d", d + i);
   rep(i, 0, n) pw[i] = qpow(2, i * (i - 1ll) / 2 % (mod - 1));
   rep(i, 0, n) {
      c[i][0] = c[i][i] = 1;
      rep(j, 1, i - 1) {
         c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
      }
   }
   a[1] = 1;
   rep(i, 2, n) {
      a[i] = pw[i];
      rep(j, 1, i - 1) {
         (a[i] += mod - 1ll * c[i][j] * a[j] % mod * pw[i - j] % mod) %= mod;
      }
   }
   f[0] = 0;
   rep(i, 1, n) {
      rep(j, 1, i) {
         (f[i] += 1ll * c[i][j] * a[j] % mod * (f[i - j] + 1ll * pw[i - j] * j % mod * d[j] % mod) % mod) %= mod;
      }
   }
   rep(x, 1, n) {
      int res = 1ll * f[x] * qpow(1ll * x * pw[x] % mod, mod - 2) % mod;
      printf("%d\n", res);
   }
   return 0;   
}