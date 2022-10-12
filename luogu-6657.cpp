#include <bits/stdc++.h>
#define debug(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 110, M = 2e6 + 10, mod = 998244353;
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
int a[N][N];
int gauss(int n) {
   int ans = 1, rev = 0;
   rep(i, 1, n) {
      int k = 0;
      rep(j, i, n) if(a[j][i]) { k = j; break ; }
      if(k != i) {
         rev ^= 1;
         rep(j, i, n) swap(a[i][j], a[k][j]);
      }
      int inv = qpow(a[i][i], mod - 2);
      ans = 1ll * ans * a[i][i] % mod;
      rep(j, i + 1, n) {
         int t = mod - (ll)a[j][i] * inv % mod;
         rep(k, i, n) {
            a[j][k] = (a[j][k] + (ll)t * a[i][k]) % mod;
         }
      }
   }
   if(rev) ans = ans ? mod - ans : 0;
   return ans;
}
int fac[M], fav[M]; 
int C(int n, int m) {
   return n < m ? 0 : 1ll * fac[n] * fav[m] % mod * fav[n - m] % mod;
}
void binom(int n) {
   fac[0] = 1;
   for(int i = 1; i <= n; i ++) fac[i] = (ll)fac[i - 1] * i % mod;
   fav[n] = qpow(fac[n], mod - 2);
   for(int i = n; i >= 1; i --) fav[i - 1] = (ll)fav[i] * i % mod;
}
int n, m, s[N], t[N];
int main() {
   int test;
   scanf("%d", &test);
   binom(2e6);
   while(test --) {
      scanf("%d%d", &n, &m);
      rep(i, 1, m) scanf("%d%d", s + i, t + i);
      rep(i, 1, m) rep(j, 1, m) a[i][j] = C(t[j] - s[i] + n - 1, n - 1);
      printf("%d\n", gauss(m));
   }
   return 0;
}