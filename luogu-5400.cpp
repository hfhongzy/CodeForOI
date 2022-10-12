#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 5e6 + 10;
const int mod = 998244353;
int n, m, l, k, fac[N], fav[N], f[N], g[N];
int qpow(int a, int b) {
  int ans = 1;
  for(; b >= 1; b >>= 1, a = (ll)a * a % mod)
    if(b & 1) ans = (ll)ans * a % mod;
  return ans;
}
void binom(int n) {
  fac[0] = 1;
  rep(i, 1, n) fac[i] = (ll)fac[i - 1] * i % mod;
  fav[n] = qpow(fac[n], mod - 2);
  per(i, n, 1) fav[i - 1] = (ll)fav[i] * i % mod;
}
int C(int n, int m) {
  return (ll)fac[n] * fav[m] % mod * fav[n - m] % mod;
}
int main() {
  int test;
  scanf("%d", &test);
  int la = 0;
  while(test --) {
    scanf("%d%d%d%d", &n, &m, &l, &k);
    int t = min(n, min(m, l));
    if(t > la) binom(t), la = t;
    f[0] = 1;
    int u = (ll)n * m % mod * l % mod;
    rep(i, 1, t) {
      g[i] = (u + 1ll * (mod - n + i) * (m - i) % mod * (l - i)) % mod;
      f[i] = (ll)f[i - 1] * g[i] % mod;
    }
    f[t] = qpow(f[t], mod - 2);
    per(i, t, k) f[i - 1] = (ll)f[i] * g[i] % mod;
    int ans = 0;
    int x = 1, y = 1, z = 1;
    rep(i, 1, k - 1) {
      x = (ll)x * (n - i + 1) % mod;
      y = (ll)y * (m - i + 1) % mod;
      z = (ll)z * (l - i + 1) % mod;
    }
    rep(i, k, t) {
      x = (ll)x * (n - i + 1) % mod;
      y = (ll)y * (m - i + 1) % mod;
      z = (ll)z * (l - i + 1) % mod;
      f[i] = (ll)f[i] * x % mod * y % mod * z % mod;
      if((k - i) & 1) ans = (ans + (ll)C(i, k) * (mod - f[i])) % mod;
      else ans = (ans + (ll)C(i, k) * f[i]) % mod;
    }
    printf("%d\n", ans); 
  }
  return 0;
}