#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e7 + 1e5 + 10;
const int M = 1e5 + 10;
const int mod = 998244353;

int m, n, a, b, p, q;
int fac[N], fav[N], f[M], pwa[N], pwb[N], ipwa[N];
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
void init() {
   fac[0] = 1;
   rep(i, 1, n + m) fac[i] = 1ll * fac[i - 1] * i % mod;
   fav[n + m] = qpow(fac[n + m], mod - 2);
   per(i, n + m, 1) fav[i - 1] = 1ll * fav[i] * i % mod;
   pwa[0] = pwb[0] = 1;
   rep(i, 1, n + m) {
      pwa[i] = 1ll * pwa[i - 1] * a % mod;
   }
   ipwa[n + m] = qpow(pwa[n + m], mod - 2);
   per(i, n + m, 1) ipwa[i - 1] = 1ll * ipwa[i] * a % mod;
   rep(i, 1, n) pwb[i] = 1ll * pwb[i - 1] * b % mod;
}
int C(int n, int m) {
   return n < m ? 0 : 1ll * fac[n] * fav[m] % mod * fav[n - m] % mod;
}
int main() {
   scanf("%d%d%d%d%d%d", &m, &n, &a, &b, &p, &q);
   init();
   rep(i, 1, n) scanf("%d", f + i);
   int x, y;
   rep(T, 1, q) {
      scanf("%d%d", &x, &y);
      if(x == p) printf("%d\n", f[y]);
      else if(x > p) {
         int ans = 0;
         rep(i, 0, x - p) {
            if(y - i <= 0) break ;
            ans = (ans + 1ll * f[y - i] * pwa[x - p - i] % mod * pwb[i] % mod * C(x - p, i)) % mod;
         }
         printf("%d\n", ans);
      } else {
         int ans = 0;
         rep(i, 1, y) {
            ans = (ans + 1ll * C(p - x + y - i - 1, p - x - 1) * ((y - i) % 2 ? mod - 1ll : 1ll) % mod * pwb[y - i] % mod * ipwa[p - x + y - i] % mod * f[i]) % mod;
         }
         printf("%d\n", ans);
      }
   }
   return 0;
}