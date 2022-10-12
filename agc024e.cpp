#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 310;
int n, k, mod, f[N][N], g[N][N], C[N][N];
int add(int x, int y) { return (x += y) >= mod ? x - mod : x; }
int main() {
  scanf("%d%d%d", &n, &k, &mod);
  rep(i, 0, n + 1) {
    C[i][0] = 1;
    rep(j, 1, i) C[i][j] = add(C[i - 1][j - 1], C[i - 1][j]);
  }
  rep(i, 0, k) f[1][i] = 1, g[1][i] = (k - i + 1) % mod;
  rep(i, 1, n + 1) per(j, k, 0) {
    rep(s, 1, i - 1) {
      f[i][j] = (f[i][j] + (ll)C[i - 2][s - 1] * g[s][j + 1] % mod * f[i - s][j]) % mod;
    }
    g[i][j] = add(g[i][j + 1], f[i][j]);
  }
  printf("%d\n", f[n + 1][0]);
  return 0;
}