#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int mod = 998244353;
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
const int N = 1e6 + 10;
int fac[N], fav[N], n, k; 
int C(int n, int m) {
   return n < m ? 0 : 1ll * fac[n] * fav[m] % mod * fav[n - m] % mod;
}
void binom(int n) {
   fac[0] = 1;
   for(int i = 1; i <= n; i ++) fac[i] = 1ll * fac[i - 1] * i % mod;
   fav[n] = qpow(fac[n], mod - 2);
   for(int i = n; i >= 1; i --) fav[i - 1] = 1ll * fav[i] * i % mod;
}
int S(int n, int m) {
   int ans = 0;
   rep(i, 0, m) {
      int res = 1ll * C(m, i) * qpow(m - i, n) % mod;
      if(i & 1) (ans += mod - res) %= mod;
      else (ans += res) %= mod;
   }
   return 1ll * ans * fav[m] % mod;
}
int main() {
   scanf("%d%d", &n, &k); binom(n);
   int ans = 1ll * S(n - 2, n - k) * fac[n - k] % mod * C(n, k) % mod;
   printf("%d\n", ans);
   return 0;   
}