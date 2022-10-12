#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 52;
int n, m, a[N][N], s[N][N], g[N][N][N * N];
int main() {
   scanf("%d%d", &n, &m);
   for(int i = 1; i <= n; i ++) {
      for(int j = 1; j <= n - i + 1; j ++) {
         scanf("%d", &a[i][j]);
         s[i][j] = s[i - 1][j] + a[i][j];
      }
   }
   memset(g, -1, sizeof g); g[0][n + 1][0] = 0;
   for(int j = n; j >= 1; j --) {
      for(int i = n - j + 1; i >= 0; i --) {
         int x, t = (1 + n - j + 1) * (n - j + 1) / 2;
         for(int k = i; k <= t + i; k ++) {
            if(~ g[max(0, i - 1)][j + 1][k - i]) {
               x = s[i][j] + g[max(0, i - 1)][j + 1][k - i];
            } else {
               x = -1;
            }
            g[i][j][k] = max(g[i + 1][j][k], x);
         }
      }
   }
   printf("%d\n", g[0][1][m]);
   return 0;
}
/*
14 15 4  3 23
33 33 76 2
2  13 11
22 23
31
*/