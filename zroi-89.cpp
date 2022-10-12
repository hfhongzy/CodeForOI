#include <bits/stdc++.h>
#define UPD(x, y) x = (x + y) % mod
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int M = 2e5 + 10;
const int N = 102;
int n, X, mod, fac[M], fav[M], f[N][N * N][N], w[N];
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
void init(int n) {
   fac[0] = 1;
   rep(i, 1, n) fac[i] = (ll) fac[i - 1] * i % mod;
   fav[n] = qpow(fac[n], mod - 2);
   per(i, n, 1) fav[i - 1] = (ll) fav[i] * i % mod;
}
int C(int n, int m) {
   return n < m || n < 0 || m < 0 ? 0 : (ll) fac[n] * fav[m] % mod * fav[n - m] % mod;
}
int main() {
   scanf("%d%d%d", &n, &X, &mod);
   init(n + X);
   f[1][0][0] = 1; w[1] = 0; int t = 0;
   rep(i, 1, n - 1) {
      rep(j, 0, w[i]) {
         rep(k, 0, i) if(t = f[i][j][k]) {
            UPD(f[i + 1][j + i + 1][k], 2ll * t);
            UPD(f[i + 1][j][k + 1], 2ll * t);
            if(k) {
               UPD(f[i + 1][j + 2 * (i + 1)][k - 1], (ll) k * t);
               UPD(f[i + 1][j + i + 1][k], 2ll * k * t);
               UPD(f[i + 1][j][k + 1], (ll) k * t);
               w[i + 1] = max(w[i + 1], j + 2 * (i + 1));
            } else {
               w[i + 1] = max(w[i + 1], j + i + 1);
            }
         }
      }
   }
   int ans = 0;
   rep(i, 0, w[n]) {
      UPD(ans, (ll) f[n][i][0] * C(X - i - 1 + n, n));
   }
   printf("%d\n", ans);
   return 0;
}