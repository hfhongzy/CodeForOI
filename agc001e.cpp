#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int M = 2e5 + 10;
const int N = 2005;
const int mod = 1e9 + 7;
int n, a[M], b[M], f[N + N][N + N];
int qpow(int a, int b) {
  int ans = 1;
  for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
    if(b & 1) ans = (ll) ans * a % mod;
  return ans;
}
int add(int x, int y) { return (x += y) >= mod ? x - mod : x; }
void upd(int &x, int y) { (x += y) >= mod ? x -= mod : 0; }
int fac[N * 4], fav[N * 4]; 
ll C(int n, int m) {
  return (ll)fac[n] * fav[m] % mod * fav[n - m];
}
void binom(int n) {
  fac[0] = 1;
  for(int i = 1; i <= n; i ++) fac[i] = (ll)fac[i - 1] * i % mod;
  fav[n] = qpow(fac[n], mod - 2);
  for(int i = n; i >= 1; i --) fav[i - 1] = (ll)fav[i] * i % mod;
}
int main() {
  scanf("%d", &n);
  rep(i, 1, n) scanf("%d%d", a + i, b + i);
  int A = *max_element(a + 1, a + n + 1);
  int B = *max_element(b + 1, b + n + 1);
  binom(2 * (A + B));
  rep(i, 1, n) f[-a[i] + N][-b[i] + N] ++;
  rep(i, -A + N, A + N) rep(j, -B + N, B + N) upd(f[i][j], add(f[i - 1][j], f[i][j - 1]));
  int ans = 0;
  rep(i, 1, n) ans = add(ans, f[a[i] + N][b[i] + N]);
  rep(i, 1, n) ans = (ans - C(2 * (a[i] + b[i]), 2 * a[i])) % mod;
  ans = ans * ((mod + 1ll) >> 1) % mod;
  if(ans < 0) ans += mod;
  printf("%d\n", ans);
  return 0;
}