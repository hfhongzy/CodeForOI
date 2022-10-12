#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef double db;
db dp[1 << 18][18], p[20][20];
int main() {
  int n; scanf("%d", &n);
  rep(i, 0, n - 1) rep(j, 0, n - 1) scanf("%lf", p[i] + j);
  const int U = (1 << n) - 1;
  dp[U][0] = 1;
  per(s, U - 1, 1)
    rep(i, 0, n - 1) if(s >> i & 1)
      rep(j, 0, n - 1) if(!(s >> j & 1))
        dp[s][i] = max(dp[s][i], dp[s ^ (1 << j)][j] * p[j][i] + dp[s ^ (1 << j)][i] * p[i][j]);
  db ans = 0;
  rep(i, 0, n - 1) ans = max(ans, dp[1 << i][i]);
  printf("%.10f\n", ans);
  return 0;
}