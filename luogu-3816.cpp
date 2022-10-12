#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
template<typename T> void chkmax(T &x, const T &y) { if(x < y) x = y; }
const int N = 320;
int n, dp[N][N][2], res[N];
int main() {
   memset(dp, ~0x3f, sizeof dp);
   printf("%d!\n", dp[0][2][1]);
   dp[0][0][0] = 0;
   dp[1][1][0] = 1;
   dp[1][0][1] = 1; res[1] = 1;
   for(n = 2; n < N; n ++) {
      for(int x = 0; x <= n; x ++) {
         for(int i = 0; i < n; i ++) {
            chkmax(dp[n][x][1], dp[i][x][0] + dp[n - 1 - i][x][0] + n);
         }
         if(x == 0) continue ;
         for(int i = 0; i < n; i ++) {
            chkmax(dp[n][x][0], max(dp[i][x - 1][1], dp[i][x - 1][0]) + max(dp[n - 1 - i][x - 1][1], dp[n - 1 - i][x - 1][0]) + n);
         }
      }
      int ans = 0;
      for(int x = 0; x <= n; x ++) {
         chkmax(ans, max(dp[n][x][0], dp[n][x][1]));
      }
      res[n] = ans;
   }
   while(~ scanf("%d", &n) && n) {
      printf("%d\n", res[n]);
   }
   return 0;
}
/*
dp[n][x][0 / 1] : n个结点的树，到叶子的黑色结点数是x，根结点是红1/黑0，深度和最大值
dp[n][x][1] = 0;
for(int i = 0; i < n; i ++) {
   chkmax(dp[n][x][0], dp[i][x][0] + dp[n - 1 - i][x][0] + n - 1);
}
dp[n][x][0] = 0;
for(int i = 0; i < n; i ++) {
   chkmax(dp[n][x][0], max(dp[i][x - 1][1], dp[i][x - 1][0]) + max(dp[n - 1 - i][x - 1][0], dp[n - 1 - i][x - 1][0]) + n - 1);
}
*/