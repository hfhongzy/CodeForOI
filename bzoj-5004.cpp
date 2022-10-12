#include <algorithm>
#include <cstdio>
using namespace std;
typedef double db;
const int N = 305;
int n, m, k, p[N], a[N];
db c[N][N], dp[N][N];
int main() {
   for(int i = 0; i < N; i ++) {
      c[i][0] = c[i][i] = 1;
      for(int j = 1; j < i; j ++)
         c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
   }
   int test; scanf("%d", &test);
   while(test --) {
      scanf("%d%d", &n, &k);
      for(int i = 1; i <= n; i ++) scanf("%d", p + i);
      static bool vis[N]; fill(vis, vis + n + 1, 0); m = 0;
      for(int i = 1; i <= n; i ++) if(!vis[i]) {
         m ++; a[m] = 0; int u = i;
         while(!vis[u]) { vis[u] = 1; a[m] ++; u = p[u]; }
      }
      dp[0][0] = 1; int s = 0;
      for(int i = 1; i <= m; i ++) {
         s += a[i];
         for(int j = 0; j <= s; j ++) dp[i][j] = 0;
         for(int j = i - 1; j <= s - a[i]; j ++) {
            for(int k = 1; k <= a[i]; k ++) {
               dp[i][j + k] += dp[i - 1][j] * c[a[i]][k];
            }
         }
      }
      printf("%.9f\n", dp[m][k] / c[n][k]);
   }
   return 0;
}
/*
a1 a2 .. am, \sum ai = n
A[k] = \sum_{i = 1}^{a[k]} C(a[k], i) x^i /C(n, k)
*/