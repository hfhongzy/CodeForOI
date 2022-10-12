#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int mod = 19491001; //g = 7
const int N = 5e5 + 10;
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
int n, k, d, fac[N], fav[N]; 
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
   scanf("%d%d%d", &n, &k, &d);
   if(d == 1) return printf("%d\n", qpow(k, n)), 0;
   binom(k);
   if(d == 2) {
      int ans = 0;
      rep(i, 0, k) {
         ans = (ans + (ll)C(k, i) * qpow((mod + 2 * i - k) % mod, n)) % mod;
      }
      ans = (ll)ans * qpow((mod + 1) >> 1, k) % mod;
      printf("%d\n", ans);
      return 0;
   }
   const ll w = qpow(7, (mod - 1) / 3), w2 = w * w % mod;
   int ans = 0;
   rep(a, 0, k) rep(b, 0, k - a) {
      int c = k - a - b, t = (a + w * b + w2 * c) % mod;
      ans = (ans + (ll)fac[k] * fav[a] % mod * fav[b] % mod * fav[c] % mod * qpow(t, n)) % mod;
   }
   ans = (ll) ans * qpow(qpow(3, k), mod - 2) % mod;
   printf("%d\n", ans);
   return 0;
}