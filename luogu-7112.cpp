#include <bits/stdc++.h>
const int N = 610;
int n, mod, a[N][N];
int gauss() {
  int sgn = 1;
  for(int i = 1; i <= n; i ++) {
    int k = i;
    for(int j = i; j <= n; j ++) if(a[j][i]) { k = j; break ; }
    if(!a[k][i]) return 0;
    if(k != i) {
      for(int j = i; j <= n; j ++) std::swap(a[i][j], a[k][j]);
      sgn *= -1;
    }
    for(int j = i + 1; j <= n; j ++) {
      while(1) {
        int x = a[i][i], y = a[j][i];
        if(y == 0) break ;
        int t = x / y;
        for(int k = i; k <= n; k ++) {
          a[i][k] = (a[i][k] - 1ll * a[j][k] * t) % mod;
          std::swap(a[i][k], a[j][k]);
        }
        sgn *= -1;
      }
    }
  }
  int ans = 1;
  for(int i = 1; i <= n; i ++)
    ans = 1ll * ans * a[i][i] % mod;
  return sgn == 1 ? (ans + mod) % mod : (mod - ans) % mod;
}
int main() {
  scanf("%d%d", &n, &mod);
  for(int i = 1; i <= n; i ++)
    for(int j = 1; j <= n; j ++)
      scanf("%d", a[i] + j), a[i][j] %= mod;
  printf("%d\n", gauss());
  return 0;
}