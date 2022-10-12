#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef double db;
const int N = 64;
int n, z[N], s[N], t, a[N], b[N];
db p[N], f[N][5050];
bool chk(db k) {
  rep(i, 0, s[n]) f[n][i] = i <= t ? 0 : k;
  per(i, n, 1) rep(j, z[i - 1], s[i - 1])
    f[i - 1][j] = j > t ? k : min(k, (f[i][j + a[i]] + a[i]) * p[i] + (f[i][j + b[i]] + b[i]) * (1 - p[i]));
  return f[0][0] < k;
}
int main() {
  scanf("%d%d", &n, &t);
  int x;
  rep(i, 1, n) {
    scanf("%d%d%d", a + i, b + i, &x);
    s[i] = s[i - 1] + b[i];
    z[i] = z[i - 1] + a[i];
    p[i] = x * 0.01;
  }
  db l = 0, r = 346821370;
  rep(T, 1, 64) {
    db k = (l + r) / 2;
    (chk(k) ? r : l) = k;
  }
  printf("%.10f\n", l);
  return 0;
}