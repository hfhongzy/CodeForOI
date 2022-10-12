#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 105, mod = 1e9 + 7;
int n, m, g[N], dp[N][N], pw[N * N], pwr[N][N], C[N][N];
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
int calc(int x, int y) {
   return x == 0 ? 1 : 1ll * pwr[x][y] * pw[y * (y - 1) / 2] % mod * g[x] % mod;
}
int main() {
   rep(i, 0, N - 1) {
      C[i][0] = C[i][i] = 1;
      rep(j, 1, i - 1) {
         C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
      }
   }
   pw[0] = 1;
   rep(i, 1, N * N - 1) pw[i] = (pw[i - 1] + pw[i - 1]) % mod;
   rep(i, 1, N - 1) {
      pwr[i][0] = 1;
      rep(j, 1, N - 1) pwr[i][j] = pwr[i][j - 1] * (pw[i] - 1ll) % mod;
   }
   g[0] = g[1] = 1;
   rep(i, 2, N - 1) {
      g[i] = pw[i * (i - 1) / 2];
      rep(j, 1, i - 1) {
         g[i] = (g[i] - (ll)C[i - 1][j - 1] * g[j] % mod * pw[(i - j) * (i - j - 1) / 2]) % mod;
      }
      if(g[i] < 0) g[i] += mod;
   }
   rep(i, 0, N - 1) {
      dp[i][0] = pw[i * (i - 1) / 2];
      rep(j, 1, N - 1 - i) {
         rep(x, 0, i) rep(y, 0, j - 1) {
            dp[i][j] = (dp[i][j] + (ll) dp[x][y] * calc(i - x, j - y) % mod * C[i][x] % mod * C[j - 1][y]) % mod;
         }
      }
   }
   // cerr << clock() / (double) CLOCKS_PER_SEC << endl;
   int test; scanf("%d", &test);
   while(test --) {
      scanf("%d%d", &n, &m);
      printf("%d\n", dp[n - m][m]);
   }
   return 0;
}
/*
8
1 1
2 2
3 1
10 0
10 1
10 8
10 9
10 10
*/