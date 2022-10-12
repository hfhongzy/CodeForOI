#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e7 + 50, mod = 998244353;
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
inline int add(int x, int y) { return x + y >= mod ? x + y - mod : x + y; }
inline int dec(int x, int y) { return x - y < 0 ? x - y + mod : x - y; }
inline void upd(int &x, const int &y) { (x += y) >= mod ? x -= mod : 0; }

int n, k, c, p[N], pw[N], s1[N], s2[N], fac[N], fav[N];
bool tag[N];
void sieve(int n) {
   pw[1] = s1[1] = s2[1] = 1;
   rep(i, 2, n) {
      if(!tag[i]) { p[++ c] = i; pw[i] = qpow(i, k); }
      rep(j, 1, c) {
         if(i * p[j] > n) break ;
         tag[i * p[j]] = 1;
         pw[i * p[j]] = (ll) pw[i] * pw[p[j]] % mod;
         if(i % p[j] == 0) break ;
      }
      s1[i] = add(s1[i - 1], pw[i]);
      s2[i] = (s2[i - 1] + (ll) pw[i] * i) % mod;
   }
   fac[0] = 1;
   rep(i, 1, n) fac[i] = (ll) fac[i - 1] * i % mod;
   fav[n] = qpow(fac[n], mod - 2);
   per(i, n, 1) fav[i - 1] = (ll) fav[i] * i % mod;
}
int SPow(int n, int k) { // \sum_{i = 1}^n i^k
   const int *y = k == ::k ? s1 : s2;
   if(n <= k + 2) return y[n];
   if(n >= mod) return add(SPow(mod - 1, k), SPow(n - mod, k));
   static int pdl[N], pdr[N];
   pdl[0] = pdr[k + 3] = 1;
   rep(i, 1, k + 2) pdl[i] = (ll) pdl[i - 1] * (n - i) % mod;
   per(i, k + 2, 1) pdr[i] = (ll) pdr[i + 1] * (n - i) % mod;
   int ans = 0;
   rep(i, 1, k + 2) {
      int t = (ll) fav[i - 1] * fav[k + 2 - i] % mod * y[i] % mod * pdl[i - 1] % mod * pdr[i + 1] % mod;
      ans = (k + 2 - i) & 1 ? dec(ans, t) : add(ans, t);
   }
   ans = (ll) ans * pdr[1] % mod * qpow(pdr[1], mod - 2) % mod;
   return ans;
}
int main() {
   scanf("%d%d", &n, &k); sieve(k + 3);
   ll ans = (2ll * SPow(n, k + 1) + mod - SPow(2 * n, k + 1) + mod - (2ll * n + 2 + qpow(2, k)) * SPow(n, k) % mod + (2ll * n + 1) * SPow(2 * n, k) % mod) % mod;
   ans = ans * qpow(n, mod - 2) % mod;
   printf("%d\n", (int) ans);
   // cerr << clock() / (double) CLOCKS_PER_SEC << "\n";
   return 0;
}