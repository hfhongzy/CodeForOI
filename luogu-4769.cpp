#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 6e5 + 10;
const int mod = 998244353;
int qpow(int a, int b) {
  int ans = 1;
  for(; b >= 1; b >>= 1, a = (ll)a * a % mod)
    if(b & 1) ans = (ll)ans * a % mod;
  return ans;
}
int n, q[N], fac[N * 2], fav[N * 2];
void init(int n) {
  fac[0] = 1;
  rep(i, 1, n) fac[i] = (ll)fac[i - 1] * i % mod;
  fav[n] = qpow(fac[n], mod - 2);
  per(i, n, 1) fav[i - 1] = (ll)fav[i] * i % mod;
}
int C(int n, int m) {
  return (ll)fac[n] * fav[m] % mod * fav[n - m] % mod;
}
int calc(int x, int y) {
  return y > n ? 0 : (C(2 * n - x - y, n - x) - C(2 * n - x - y, n - x + 1) + mod) % mod;
}
int main() {
  init(int(6e5) * 2);
  int test;
  scanf("%d", &test);
  rep(T, 1, test) {
    scanf("%d", &n);
    static bool vis[N];
    rep(i, 1, n) scanf("%d", q + i);
    fill(vis, vis + n + 1, 0);
    int res = 0, mx = 0, mn = 1;
    rep(k, 0, n - 1) {
      res = (res + calc(k, max(mx, q[k + 1]) + 1)) % mod;
      vis[q[k + 1]] = 1;
      if(mx < q[k + 1]) mx = q[k + 1];
      else if(mn != q[k + 1]) break ;
      while(vis[mn]) ++ mn;
    }
    printf("%d\n", res);
  }
  return 0;
}