#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1520;
const int mod = 998244353;
int n, m, k, C[N * 2][N * 2], a[N], b[N], f[N][N][2], g[N][N][2];
int add(int x, int y) {
  return (x += y) >= mod ? x -= mod : x;
}
int main() {
  rep(i, 0, 3000) {
    C[i][0] = 1;
    rep(j, 1, i)
      C[i][j] = add(C[i - 1][j - 1], C[i - 1][j]);
  }
  int test;
  scanf("%d", &test);
  while(test --) {
    scanf("%d%d%d", &n, &m, &k);
    rep(i, 1, n) scanf("%d", a + i);
    rep(i, 1, n) scanf("%d", b + i);
    sort(a + 1, a + n + 1, greater<int>());
    sort(b + 1, b + n + 1, greater<int>());
    f[0][0][1] = 1;
    g[0][0][1] = 0;
    rep(i, 1, n) {
      f[i][0][0] = 1;
      g[i][0][0] = 0;
      rep(j, 1, i) {
        f[i][j][0] = add(f[i - 1][j][0], f[i - 1][j][1]);
        f[i][j][1] = (f[i - 1][j - 1][0] + f[i - 1][j - 1][1]) * (ll)a[i] % mod;
        g[i][j][0] = add(g[i - 1][j][0], g[i - 1][j][1]);
        g[i][j][1] = ((ll)C[i - 1][j - 1] * b[i] + g[i - 1][j - 1][0] + g[i - 1][j - 1][1]) % mod;
      }
    }
    int ans = 0;
    rep(i, k - 1, n) {
      int t = 0;
      rep(j, 1, n) {
        t = (t + (ll)C[2 * n - i - j][m - k] * b[j]) % mod;
      }
      ans = (ans + (ll)f[i][k - 1][1] * t) % mod;
    }
    rep(i, 0, k - 2) {
      int t = 0;
      rep(j, k - i, n) {
        t = (t + (ll)C[n - j][m - k] * g[j][k - i][1]) % mod;
      }
      ans = (ans + (f[n][i][0] + f[n][i][1]) * (ll)t) % mod;
    }
    printf("%d\n", ans);
  }
  return 0;
}