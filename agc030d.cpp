#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 3005;
const int mod = 1e9 + 7;
const long long inv2 = (mod + 1) >> 1;
int n, m, a[N], f[N][N], g[N][N];
int main() {
  scanf("%d%d", &n, &m);
  rep(i, 1, n) scanf("%d", a + i);
  rep(i, 1, n) rep(j, 1, n) f[i][j] = a[i] > a[j];
  int a, b;
  rep(i, 1, m) {
    scanf("%d%d", &a, &b);
    rep(u, 1, n) g[a][u] = f[a][u], g[u][a] = f[u][a], g[b][u] = f[b][u], g[u][b] = f[u][b];
    f[a][b] = f[b][a] = (g[b][a] + g[a][b]) * inv2 % mod;
    rep(u, 1, n) {
      if(u != a && u != b) {
        f[u][b] = (g[u][b] + g[u][a]) * inv2 % mod;
        f[b][u] = (g[b][u] + g[a][u]) * inv2 % mod;
      }
      if(u != b && u != a) {
        f[u][a] = (g[u][a] + g[u][b]) * inv2 % mod;
        f[a][u] = (g[a][u] + g[b][u]) * inv2 % mod;
      }
    }
  }
  int ans = 0;
  rep(i, 1, n) rep(j, i + 1, n) ans = (ans + f[i][j]) % mod;
  rep(i, 1, m) ans = (ans + ans) % mod;
  printf("%d\n", ans);
  return 0;
}