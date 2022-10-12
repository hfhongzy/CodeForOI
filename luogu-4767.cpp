#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 3010;
const int INF = 1 << 30;
int n, m, a[N], s[N], f[N][N], g[N][N];
int calc(int l, int r) {
   int mid = (l + r) >> 1;
   return (2 * mid - l - r) * a[mid] - s[mid - 1] + s[l - 1] + s[r] - s[mid];
}
int main() {
   scanf("%d%d", &n, &m);
   rep(i, 1, n) scanf("%d", a + i);
   // sort(a + 1, a + n + 1);
   rep(i, 1, n) s[i] = s[i - 1] + a[i];
   rep(i, 1, m) f[i][i] = 0, g[i][i] = i - 1;
   rep(i, m + 1, n) g[m + 1][i] = i - 1;
   rep(i, 1, n) f[0][i] = INF;
   f[0][0] = 0;
   rep(l, 2, n - m + 1) rep(i, 1, m) {
      int j = i + l - 1;
      f[i][j] = INF;
      // printf("g[%d][%d] : %d to %d\n", i, j, g[i][j - 1], g[i + 1][j]);
      rep(k, g[i][j - 1], g[i + 1][j]){
         int w = f[i - 1][k] + calc(k + 1, j);
         if(w < f[i][j]) {
            f[i][j] = w; g[i][j] = k;
         }
      }
      // printf("f(%d, %d) = %d\n", i, j, f[i][j]);.
   }
   printf("%d\n", f[m][n]);
   return 0;
}