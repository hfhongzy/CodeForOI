#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; i ++)
using namespace std;
const int N = 420, mod = 1e9 + 7;
int n, ans, a[N], dp[N][N];
int main() {
   scanf("%d", &n);
   rep(i, 1, n)
      scanf("%d", a + i);
   rep(i, 1, n) {
      dp[0][0] = 1;
      rep(j, 1, n) rep(k, 0, N - 1) {
         dp[j][k] = dp[j - 1][k];
         if(j != i && (k ^ a[j]) < N)
            (dp[j][k] += dp[j - 1][k ^ a[j]]) %= mod;
      }
      rep(j, a[i], N - 1) {
         (ans += dp[n][j]) %= mod;
      }
   }
   printf("%d\n", ans);
   return 0;
}