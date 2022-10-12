#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, m, pw[512], x[512], y[512], g[21][1 << 20], f[21][1 << 20], h[21][1 << 20], cnt[1 << 20], inv[22];
int add(int a, int b) { return (a += b) >= mod ? a - mod : a; }
void fwt(int *a) {
  for(int i = 1; i < (1 << n); i <<= 1)
    for(int j = 0; j < (1 << n); j += i << 1)
      for(int k = 0; k < i; k ++)
        a[j + i + k] = add(a[j + i + k], a[j + k]);
}
void ifwt(int *a) {
  for(int i = 1; i < (1 << n); i <<= 1)
    for(int j = 0; j < (1 << n); j += i << 1)
      for(int k = 0; k < i; k ++)
        a[j + i + k] = add(a[j + i + k], mod - a[j + k]);
}
int main() {
  scanf("%d%d", &n, &m);
  for(int i = 0; i < m; i ++) scanf("%d%d", x + i, y + i), x[i] --, y[i] --;
  for(int i = 0; i <= m; i ++) pw[i] = i ? add(pw[i - 1], pw[i - 1]) : 1;
  for(int i = 1; i <= n; i ++) inv[i] = i > 1 ? (mod - mod / i) * (ll)inv[mod % i] % mod : 1;
  for(int i = 1; i < (1 << n); i ++) {
    cnt[i] = cnt[i & (i - 1)] + 1;
    int c = 0;
    for(int j = 0; j < m; j ++)
      c += (i >> x[j] & 1) && (i >> y[j] & 1);
    g[cnt[i]][i] = pw[c];
  }
  for(int i = 1; i <= n; i ++) fwt(g[i]);
  for(int i = 1; i <= n; i ++) {
    for(int j = 0; j < i; j ++)
      for(int k = 0; k < (1 << n); k ++)
        f[i][k] = (f[i][k] + (ll)j * f[j][k] % mod * g[i - j][k]) % mod;
    for(int k = 0; k < (1 << n); k ++)
      f[i][k] = (g[i][k] + (mod - inv[i]) * (ll)f[i][k]) % mod;
  }
  for(int i = 0; i < (1 << n); i ++) h[0][i] = 1;
  for(int i = 1; i <= n; i ++) {
    for(int j = 0; j < i; j ++)
      for(int k = 0; k < (1 << n); k ++)
        h[i][k] = (h[i][k] + (ll)h[j][k] * f[i - j][k]) % mod;
  }
  ifwt(h[n]);
  printf("%d\n", h[n][(1 << n) - 1]);
  return 0;
}