#include <algorithm>
#include <vector>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; i ++)
#define per(i, j, k) for(int i = j; i >= k; i --)
using namespace std;
const int N = 110, INF = 1e9 + 5;
int n, m, ans = 2 * INF, G[N][N], d[N][N];
int main() {
   scanf("%d%d", &n, &m);
   rep(i, 1, n) rep(j, 1, n) G[i][j] = INF;
   rep(i, 1, m) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      G[u][v] = G[v][u] = min(G[u][v], w);
   }
   rep(i, 1, n) rep(j, 1, n) d[i][j] = G[i][j];
   rep(k, 1, n) {
      rep(i, 1, k - 1) rep(j, i + 1, k - 1) if(G[i][k] < INF && G[k][j] < INF)
         ans = min(ans, d[i][j] + G[i][k] + G[k][j]);
      rep(i, 1, n) rep(j, 1, n)
         d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
   }
   if(ans >= 2 * INF) puts("No solution.");
   else printf("%d\n", ans);
   return 0;
}