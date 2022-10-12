#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1010;
int test, n, m, ans, a[N][N], f[N][N];
int main() {
  scanf("%d", &test);
  while(test --) {
    scanf("%d%d", &n, &m); ans = 0;
    rep(i, 1, n) rep(j, 1, m) scanf("%d", a[i] + j);
    rep(i, 0, m) f[n + 1][i] = 0;
    per(i, n, 1) rep(j, 1, m)
      f[i][j] = max(f[i + 1][j], max(f[i][j - 1], f[i + 1][j - 1] + a[i][j]));
    printf("%d\n", f[1][m]);
  }
  return 0;
}