#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 405, INF = 1e9;
int n, m, s[N], t[N];
int a[N], f[N][N], g[N][N], w[N][N], ans[N][N];
int main() {
   scanf("%d", &n);
   rep(i, 1, n) {
      scanf("%d%d", s + i, t + i);
      t[i] += s[i]; a[i] = s[i]; a[i + n] = t[i];
   }
   sort(a + 1, a + 2 * n + 1);
   m = unique(a + 1, a + 2 * n + 1) - a - 1;
   rep(i, 1, n) {
      s[i] = lower_bound(a + 1, a + m + 1, s[i]) - a;
      t[i] = lower_bound(a + 1, a + m + 1, t[i]) - a;
      rep(l, 1, s[i]) rep(r, t[i], m) w[l][r] ++;
   }
   rep(i, 0, m + 1) rep(j, 0, n) f[i][j] = g[i][j] = -INF;
   f[0][0] = 0;
   rep(i, 1, m) rep(j, 0, n) rep(k, 0, i - 1) {
      f[i][j] = max(f[i][j], f[k][j] + w[k][i]);
      if(j >= w[k][i])
         f[i][j] = max(f[i][j], f[k][j - w[k][i]]);
   }
   g[m + 1][0] = 0;
   per(i, m, 1) rep(j, 0, n) rep(k, i + 1, m + 1) {
      g[i][j] = max(g[i][j], g[k][j] + w[i][k]);
      if(j >= w[i][k])
         g[i][j] = max(g[i][j], g[k][j - w[i][k]]);
   }
   rep(l, 1, m) rep(r, l, m) {
      int y = n;
      rep(x, 0, n) {
         // ans[l][r] = max(ans[l][r], min(x + y + w[l][r], f[l][x] + g[r][y]));
         while(y && x + y - 1 + w[l][r] >= f[l][x] + g[r][y - 1]) y --;
         ans[l][r] = max(ans[l][r], min(x + y + w[l][r], f[l][x] + g[r][y]));
         ans[l][r] = max(ans[l][r], min(x + y - 1 + w[l][r], f[l][x] + g[r][y - 1]));
      }
   }
   int res = 0;
   rep(i, 0, n) res = max(res, min(i, f[m][i]));
   printf("%d\n", res);
   rep(i, 1, n) {
      res = 0;
      rep(l, 1, s[i]) rep(r, t[i], m)
         res = max(res, ans[l][r]);
      printf("%d\n", res);
   }
   return 0;
}