#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
const int mod = 998244353;
int qpow(int a, int b) {
  int ans = 1;
  for(; b >= 1; b >>= 1, a = (ll)a * a % mod)
    if(b & 1) ans = (ll)ans * a % mod;
  return ans;
}
int fac[N], fav[N]; 
int C(int n, int m) {
  return (ll)fac[n] * fav[m] % mod * fav[n - m] % mod;
}
int Ci(int n, int m) {
  return (ll)fav[n] * fac[m] % mod * fac[n - m] % mod;
}
void binom(int n) {
  fac[0] = 1;
  for(int i = 1; i <= n; i ++) fac[i] = (ll)fac[i - 1] * i % mod;
  fav[n] = qpow(fac[n], mod - 2);
  for(int i = n; i >= 1; i --) fav[i - 1] = (ll)fav[i] * i % mod;
}
int n, m, ans, tot;
int main() {
  scanf("%d%d", &n, &m);
  if(n < m) swap(n, m);
  binom(n + m); tot = Ci(n + m, m) * ((mod + 1ll) >> 1) % mod;
  rep(i, 1, m) {
    ans = (ans + (ll)tot * C(2 * i, i) % mod * C(n + m - 2 * i, n - i)) % mod;
  }
  // printf("%d!\n", ans);
  ans = (ans + max(n, m)) % mod;
  printf("%d\n", ans);
  return 0;
}