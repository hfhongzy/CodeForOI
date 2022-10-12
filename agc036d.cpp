#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 505;
const ll INF = 1e17;
int n, a[N][N];
ll s1[N][N], s2[N][N], dp[N][N];
//s1: -1; s2: 1;
ll S(ll s[N][N], int xl, int xr, int yl, int yr) {
  return s[xr][yr] - s[xl - 1][yr] - s[xr][yl - 1] + s[xl - 1][yl - 1];
}
int main() {
  scanf("%d", &n);
  rep(i, 1, n) rep(j, 1, n) if(i != j) scanf("%d", a[i] + j);
  rep(i, 1, n) rep(j, 1, n) (i < j ? s1[i][j] : s2[j][i]) += a[i][j];
  rep(i, 1, n) rep(j, 1, n) s1[i][j] += s1[i - 1][j] + s1[i][j - 1] - s1[i - 1][j - 1];
  rep(i, 1, n) rep(j, 1, n) s2[i][j] += s2[i - 1][j] + s2[i][j - 1] - s2[i - 1][j - 1];
  rep(i, 0, n) fill(dp[i], dp[i] + n + 1, INF);
  rep(i, 1, n) *dp[i] = S(s1, 1, i, 1, i);
  rep(j, 0, n - 1) rep(i, j + 1, n) rep(k, i + 1, n) {
    dp[k][i] = min(dp[k][i], dp[i][j] + S(s1, i + 1, k, i + 1, k) + S(s2, j + 1, i, k + 1, n));
  }
  ll ans = INF;
  rep(j, 0, n - 1) rep(i, 1, n)
    ans = min(ans, dp[i][j] + S(s1, i + 1, n, i + 1, n));
  printf("%lld\n", ans);
  return 0;
}