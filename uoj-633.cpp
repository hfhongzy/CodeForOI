#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int N = 110;
int k;
ll n;
int dp[N][N][N];
int main() {
  scanf("%d%lld", &k, &n);
  if(n <= 100) {
    dp[1][0][1] = 1;
    rep(i, 1, n - 1) {
      rep(x, 0, i) rep(y, 0, i - x) if(dp[i][x][y]) {
        (dp[i + 1][x][y + 1] += dp[i][x][y]) %= mod;
        if(y) (dp[i + 1][x + 1][y - 1] += (ll)dp[i][x][y] * (y -  % mod) %= mod;
        if(x) (dp[i + 1][x - 1][y + 1] += (ll)dp[i][x][y] * x % mod) %= mod;
      }
    }
    int ans = dp[n][0][k];
    rep(i, 1, n - 1)
      ans -= C(n, i) * dp[n][0][k];
    printf("%d\n", dp[n][0][k]);
  }
  return 0;
}