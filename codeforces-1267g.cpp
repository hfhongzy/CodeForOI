#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef double db;
const int N = 128;
const int M = 1e4 + 5;
int n, x, s, a[N];
db dp[N][M], C[N], ans;
int main() {
  scanf("%d%d", &n, &x);
  rep(i, 1, n) scanf("%d", a + i), s += a[i];
  C[0] = 1;
  rep(i, 1, n) C[i] = C[i - 1] / i * (n - i + 1);
  dp[0][0] = 1;
  rep(i, 1, n) per(j, n, 1) rep(k, a[i], s)
    dp[j][k] += dp[j - 1][k - a[i]];
  rep(i, 0, n - 1) {
    db t = 0;
    rep(j, 0, s)
      t += dp[i][j] * min((n * 1.0 / (n - i) + 1) * x / 2, (s - j) * 1.0 / (n - i));
    ans += t / C[i];
  }
  printf("%.12f\n", ans);
  return 0;
}