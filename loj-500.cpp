#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 105;
const int INF = 1 << 29;
int n, m, a[N], b[N], dp[N][N];
bool check(double k) {
   rep(i, 0, n) fill(dp[i], dp[i] + m + 1, INF);
   dp[0][1] = m;
   rep(i, 1, n) rep(x, 1, m) {
      int y = max(1, dp[i - 1][x]);
      if(y == INF) continue ;
      int l = min(m, (int)(x + k / b[i]));
      rep(j, x, l) dp[i][j] = min(dp[i][j], (int)ceil( y - (k - j * b[i] + x * b[i]) / a[i] ));
      if(dp[i][m] <= 1) return 1;
   }
   return 0;
}
int main() {
   scanf("%d%d", &n, &m); ++ m;
   rep(i, 1, n) {
      scanf("%d%d", a + i, b + i);
   }
   int l = 1, r = 2e8, mid, ans;
   while(l <= r) {
      mid = (l + r) >> 1;
      if(check(mid)) r = (ans = mid) - 1;
      else l = mid + 1;
   }
   printf("%d\n", ans);
   return 0;
}