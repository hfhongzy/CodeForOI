#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 2e4 + 5;
int n, a[N], b[N], c[N], ch[N][2];
ll dp[N][41][41];
#define calc(id, i, j) (ll) c[id - n + 1] * (a[id - n + 1] + i) * (b[id - n + 1] + j)
#define ddp(x, y, z) (x >= n ? calc(x, y, z) : dp[x][y][z])
void dfs(int u, int dx = 0, int dy = 0) {
   if(u >= n) return ;
   int x = ch[u][0], y = ch[u][1];
   dfs(x, dx + 1, dy); dfs(y, dx, dy + 1);
   for(int i = 0; i <= dx; i ++) {
      for(int j = 0; j <= dy; j ++) {
         dp[u][i][j] = min(ddp(x, i + 1, j) + ddp(y, i, j), ddp(x, i, j) + ddp(y, i, j + 1));
      }
   }
}
int main() {
   scanf("%d", &n);
   for(int x, y, i = 1; i < n; i ++) {
      scanf("%d%d", &x, &y);
      ch[i][0] = x > 0 ? x : n - 1 - x;
      ch[i][1] = y > 0 ? y : n - 1 - y;
   }
   for(int i = 1; i <= n; i ++)
      scanf("%d%d%d", a + i, b + i, c + i);
   dfs(1);
   printf("%lld\n", dp[1][0][0]);
   return 0;
}