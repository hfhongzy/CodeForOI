#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef double db;
const int N = 70;
const db inf = 1e9;
int n;
db p[N][N], f[N * 2][N], g[N * 2][N];
void solve(int u, int l, int r) {
  if(l == r) { f[u][l] = 1; g[u][l] = 0; return ; }
  int m = (l + r) >> 1;
  solve(u * 2, l, m);
  solve(u * 2 + 1, m + 1, r);
  rep(i, l, m) {
    db s = 0;
    rep(j, m + 1, r)
      s += f[u * 2 + 1][j] * p[i][j];
    f[u][i] = f[u * 2][i] * s;
  }
  rep(i, m + 1, r) {
    db s = 0;
    rep(j, l, m)
      s += f[u * 2][j] * p[i][j];
    f[u][i] = f[u * 2 + 1][i] * s;
  }
  int v = (r - l + 1) / 2;
  db t = 0;
  rep(i, m + 1, r) t = max(t, g[u * 2 + 1][i]);
  rep(i, l, m) g[u][i] = g[u * 2][i] + t + f[u][i] * v;
  t = 0;
  rep(i, l, m) t = max(t, g[u * 2][i]);
  rep(i, m + 1, r) g[u][i] = g[u * 2 + 1][i] + t + f[u][i] * v;
}
int main() {
  scanf("%d", &n);
  int x;
  rep(i, 1, (1 << n)) rep(j, 1, (1 << n))
    scanf("%d", &x), p[i][j] = x * 0.01;
  solve(1, 1, 1 << n);
  db mx = 0;
  rep(i, 1, (1 << n)) mx = max(mx, g[1][i]);
  printf("%.10f\n", mx);
  return 0;
}