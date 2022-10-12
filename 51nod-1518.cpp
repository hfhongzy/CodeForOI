#include <algorithm>
#include <cstring>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; i ++)
#define per(i, j, k) for(int i = j; i >= k; i --)
using namespace std;
const int N = 18, mod = 1e9 + 7;
int ans[N][N], tot[N][N];
void upd(int &x, const int &y) {
   (x += y) >= mod ? x -= mod : 0;
}
void solve(int n, int m) {
   static int dp[2][1 << 16];
   memset(dp, 0, sizeof dp); dp[0][0] = 1;
   int cur = 0;
   rep(i, 1, n) {
      rep(j, 1, m) {
         cur ^= 1; fill(dp[cur], dp[cur] + (1 << m), 0);
         rep(st, 0, (1 << m) - 1) if(dp[cur ^ 1][st]) {
            if(st >> (j - 1) & 1) {
               upd(dp[cur][st ^ (1 << (j - 1))], dp[cur ^ 1][st]);
            } else {
               if(i < n)
                  upd(dp[cur][st ^ (1 << (j - 1))], dp[cur ^ 1][st]);
               if(j < m && !(st >> j & 1))
                  upd(dp[cur][st | (1 << j)], dp[cur ^ 1][st]);
            }
         }
      }
      tot[i][m] = dp[cur][0];
   }
}
void solve_ans(int n, int m) {
   static int dp[N], f[N], a[N], cnt;
   rep(i, 0, (1 << (n - 1)) - 1) {
      a[cnt = 1] = 1;
      rep(j, 0, n - 2) if(i >> j & 1) {
         a[++ cnt] = 1;
      } else a[cnt] ++;
      rep(j, 1, m) {
         f[j] = 1;
         rep(k, 1, cnt) {
            f[j] = 1ll * f[j] * tot[a[k]][j] % mod;
         }
      }
      rep(j, 1, m) {
         dp[j] = f[j];
         rep(k, 1, j - 1) {
            upd(dp[j], mod - 1ll * dp[k] * f[j - k] % mod);
         }
      }
      if(__builtin_popcount(i) & 1) {
         rep(j, 1, m) upd(ans[n][j], mod - dp[j]);
      } else {
         rep(j, 1, m) upd(ans[n][j], dp[j]);
      }
   }
}
int main() {
   rep(m, 1, 16) solve(16, m);
   rep(n, 1, 16) solve_ans(n, 16);
   for(int n, m; ~ scanf("%d%d", &n, &m); ) {
      printf("%d\n", ans[n][m]);
   }
   return 0;
}