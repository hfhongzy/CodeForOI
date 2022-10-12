#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef double db;
const int N = 1024;
int n, m, x, y;
db f[N][N], a[N], c[N];
int main() {
  scanf("%d%d%d%d", &n, &m, &x, &y);
  n -= x - 1;
  if(m == 1) {
    printf("%.6f\n", 2 * (n - 1.0));
    return 0;
  }
  rep(i, 1, m) f[n][i] = 0;
  per(i, n - 1, 1) {
    rep(j, 1, m) {
      a[j] = -3 + (j == 1 || j == m);
      c[j] = f[i + 1][j] + 3 + (1 < j && j < m);
    }
    rep(j, 1, m - 1) {
      a[j + 1] -= 1 / a[j];
      c[j + 1] -= c[j] / a[j];
    }
    f[i][m + 1] = 0;
    per(j, m, 1) {
      f[i][j] = (f[i][j + 1] + c[j]) / (-a[j]);
    }
  }
  printf("%.6f\n", f[1][y]);
  return 0;
}