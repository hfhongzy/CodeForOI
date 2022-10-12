#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 65;
int test, n, c[N];
ll mod, ans, C[N][N];
ll mul(ll a, ll b) {
   ll t = a * b - (ll)((long double) a / mod * b + 1e-8) * mod;
   return t < 0 ? t + mod : t;
}
ll solve(int sz) {
  static ll dp[N], g[N];
  int m = 60 / sz;
  fill(dp, dp + m + 1, 0); dp[0] = 1;
  for(int i = 1; i <= n; i ++) {
    int z = (c[i] + sz - 1) / sz;
    copy(dp, dp + m + 1, g);
    fill(dp, dp + m + 1, 0);
    for(int j = m; j >= 0; j --) {
      for(int k = z; k <= m - j; k ++) {
        (dp[j + k] += mul(g[j], C[m - j][k])) %= mod;
      }
    }
  }
  return dp[m];
}
int main() {
  scanf("%d", &test);
  while(test --) {
    scanf("%d%lld", &n, &mod); mod *= 60;
    for(int i = 0; i < N; i ++) {
      C[i][0] = C[i][i] = 1;
      for(int j = 1; j < i; j ++)
        C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    for(int i = 1; i <= n; i ++) scanf("%d", c + i);
    ans = (24 * solve(5) + 20 * solve(3) + 15 * solve(2) + solve(1)) % mod;
    printf("%lld\n", ans / 60);
  }
  return 0;
}