#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int N = 5050;
int n, a[N], c[N], inv[N], f[N][N], g[N][N];
int add(int x, int y) { return (x += y) >= mod ? x - mod : x; }
int main() {
  scanf("%d", &n);
  rep(i, 1, n) scanf("%d", a + i), c[a[i]] ++;
  inv[1] = 1;
  rep(i, 2, n) inv[i] = (mod - mod / i) * (ll)inv[mod % i] % mod;
  f[0][0] = 1;
  rep(i, 0, n) g[0][i] = 1;
  int ans = 0;
  rep(i, 1, n) {
    rep(j, 1, n) {
      f[i][j] = (ll)g[i - 1][j - 1] * c[j] % mod * inv[n - i + 1] % mod;
      g[i][j] = add(g[i][j - 1], f[i][j]);
    }
    if(i < n) {
      rep(j, 1, n)
        ans = (ans + f[i][j] * (c[j] - 1ll) % mod * inv[n - i]) % mod;
    }
  }
  printf("%d\n", ans);
  return 0;
}