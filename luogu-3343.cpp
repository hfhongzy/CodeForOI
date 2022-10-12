#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
using db = double;
using ll = long long;
const int M = 45;
int n, m, u[M + 5], v[M + 5], sz[1 << 10];
ll f[1 << 10][M + 5], g[1 << 10][M + 5], c[M + 5][M + 5];
db p[M + 5];
int main() {
  scanf("%d%d", &n, &m);
  rep(i, 0, m - 1)
    scanf("%d%d", u + i, v + i), -- u[i], -- v[i];
  rep(s, 1, (1 << n) - 1)
    rep(i, 0, m - 1)
      if(s >> u[i] & 1 && s >> v[i] & 1)
        ++ sz[s];
  rep(i, 0, n - 1) f[1 << i][0] = 1;
  **c = 1;
  rep(i, 1, m) {
    *c[i] = 1;
    rep(j, 1, i)
      c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
  }
  const int U = (1 << n) - 1;
  rep(s, 1, U) {
    int w = s & (-s);
    if(w == s) continue ;
    rep(i, 0, sz[s]) {
      for(int t = (s - 1) & s; t; t = (t - 1) & s) if((t & w) == w) {
        rep(j, 0, i)
          g[s][i] += f[t][j] * c[sz[s ^ t]][i - j];
      }
      f[s][i] = c[sz[s]][i] - g[s][i];
    }
  }
  db res = 0;
  rep(i, 1, m) p[i] = (db)f[U][i] / c[m][i];
  rep(i, 1, m) res += (p[i] - p[i-1]) * i;
  res /= m + 1;
  printf("%.6f\n", res);
  return 0;
}