#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
using ll = long long;
const int N = 610;
const int mod = 1e9 + 7;
int n, f[N * 2][N], c[N][N], cat[N], inv[N];
bool vis[N * 2];
int main() {
  scanf("%d", &n);
  rep(i, 1, n) { int x; scanf("%d", &x); vis[2 * n - x + 1] = 1; }
  rep(i, 0, n) {
    c[i][0] = 1;
    rep(j, 1, i)
      (c[i][j] = c[i - 1][j - 1] + c[i - 1][j]) %= mod;
  }
  inv[1] = 1;
  rep(i, 2, n + 1) inv[i] = (ll)inv[mod % i] * (mod - mod / i) % mod;
  cat[1] = 1;
  rep(i, 2, n) cat[i] = cat[i - 1] * (4ll * i - 2) * (i - 1) % mod * inv[i + 1] % mod;
  f[0][0] = 1;
  int H = 0;
  rep(i, 0, 2 * n - 1) {
    if(!vis[i + 1]) {
      rep(j, i - H + 1, H)
        f[i + 1][j] = (ll)f[i][j] * (j - i + H) % mod;
    } else {
      H ++;
      copy(f[i], f[i] + H, f[i + 1]);
      rep(j, 0, H - 1) if(f[i][j]) rep(k, 1, H - j)
        f[i + 1][j + k] = (f[i + 1][j + k] + (ll)f[i][j] * c[H - 1 - j][k - 1] % mod * cat[k] % mod * (k + 1)) % mod;
    }
  }
  int ans = f[n * 2][n];
  rep(i, 1, n) ans = (ll)ans * inv[2] % mod;
  printf("%d\n", ans);
  return 0;
}