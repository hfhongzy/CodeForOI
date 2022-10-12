#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2005;
const int mod = 1e9 + 7;
int qpow(int a, int b) {
  int ans = 1;
  for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
    if(b & 1) ans = (ll) ans * a % mod;
  return ans;
}
int fac[N * N], fav[N * N], f[N][N]; 
int C(int n, int m) {
  return (ll)fac[n] * fav[m] % mod * fav[n - m] % mod;
}
void binom(int n) {
  fac[0] = 1;
  for(int i = 1; i <= n; i ++) fac[i] = (ll)fac[i - 1] * i % mod;
  fav[n] = qpow(fac[n], mod - 2);
  for(int i = n; i >= 1; i --) fav[i - 1] = (ll)fav[i] * i % mod;
}
int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  if(k == 1) return puts("1"), 0;
  binom(n * k);
  rep(i, 0, n) f[i][0] = 1;
  rep(i, 1, n) rep(j, 1, i)
    f[i][j] = (f[i - 1][j] + f[i][j - 1] * (n - j + 1ll) % mod * C(n * k - i - (j - 1) * (k - 1) - 1, k - 2)) % mod;
  printf("%d\n", f[n][n]);
  return 0;
}