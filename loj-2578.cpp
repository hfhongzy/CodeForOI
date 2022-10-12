#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int N = 55;
ll n, a[N];
int m, k, fac[N], f[N], g[N];
int pw(ll n) { return n & 1 ? mod - 1 : 1; }
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
int calc(ll n) {
   int y = 0, res = 0;
   fac[0] = 1;
   rep(i, 1, k + 2) fac[i] = 1ll * fac[i - 1] * qpow(i, mod - 2) % mod;
   f[0] = g[k + 3] = 1;
   rep(i, 1, k + 2) f[i] = f[i - 1] * ((n + mod - i) % mod) % mod;
   per(i, k + 2, 1) g[i] = g[i + 1] * ((n + mod - i) % mod) % mod;
   rep(i, 1, k + 2) {
      (y += qpow(i, k)) %= mod;
      int t = 1ll * f[i - 1] * g[i + 1] % mod;
      (res += 1ll * y * t % mod * fac[i - 1] % mod * fac[k + 2 - i] % mod * pw(k + 2 - i) % mod) %= mod;
   }
   return res;
}
int calc(ll l, ll r) { return l > r ? 0 : (calc(r) - calc(l - 1) + mod) % mod; }
int main() {
   int test; scanf("%d", &test);
   while(test --) {
      scanf("%lld%d", &n, &m);
      k = m + 1;
      rep(i, 1, m) scanf("%lld", a + i);
      sort(a + 1, a + m + 1);
      ll cur = n;
      per(i, m, 1) if(a[i] == cur --) k --;
      else break ;
      int ans = 0;
      a[0] = 0; a[m + 1] = n + 1;
      rep(i, 0, m) {
         rep(j, i + 1, m + 1) {
            (ans += calc(a[j - 1] + 1 - a[i], a[j] - 1 - a[i])) %= mod;
         }
      }
      printf("%d\n", ans);
   }
   return 0;
}
/*
\sum_{i = 1}^{k + 2} y_i \prod {j != i} (x - xj) / (xi - xj)
分母：1..i-1 * (-1)*(-2)*...*(i-(k+2))
分子：(n-1)*.*(n-(k+2))
*/