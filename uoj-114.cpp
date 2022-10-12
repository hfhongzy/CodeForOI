#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 512;
const int mod = 998244353;
int n, a[N], m, c[N], pw[N];
int f[N][N], g[N][N];
int solve() {
  if(m == 1) return 1;
  rep(l, 1, m) f[l][l] = 1;
  rep(l, 2, m + 1) f[l][l - 1] = 1;
  rep(l, 1, m) {
    g[l][l] = 0;
    rep(r, l + 1, m)
      g[l][r] = g[l][r - 1] + (c[l] < c[r]);
  }
  per(l, m, 1) rep(r, l + 1, m) {
    f[l][r] = (ll)f[l + 1][r] * pw[g[l][r]] % mod;
    rep(k, l + 1, r) if(c[l] > c[k]) {
      f[l][r] = (f[l][r] + (ll)f[l + 1][k - 1] * f[k][r] % mod * pw[g[l][k - 1]]) % mod;
    }
  }
  return f[2][m];
}
int main() {
  scanf("%d", &n);
  rep(i, 1, n) scanf("%d", a + i);
  *pw = 1;
  rep(i, 1, n) pw[i] = pw[i - 1] * 2 % mod;
  vector<int> vis(n + 1);
  int res = 1;
  rep(i, 1, n) if(!vis[i]) {
    m = 0;
    for(int u = i; !vis[u]; u = a[u]) {
      c[++ m] = u; vis[u] = 1;
    }
    res = (ll)res * solve() % mod;
  }
  printf("%d\n", res);
  return 0;
}