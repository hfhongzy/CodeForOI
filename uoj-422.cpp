#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 105;
const int M = 605;
const int mod = 998244353;
int n, m, f[2][1 << 7][M];
char s[N][N];
int main() {
  scanf("%d%d", &n, &m);
  rep(i, 1, n) scanf("%s", s[i] + 1);
  if(n > m) {
    rep(i, 1, n) rep(j, i, n) swap(s[i][j], s[j][i]);
    swap(n, m);
  }
  int s = 2 * n * m - n - m, c = 0;
  f[c][0][0] = 1;
  rep(i, 1, n) rep(j, 1, m) {
    c ^= 1;
    rep(s, 0, (1 << (m + 1)) - 1) rep(k, 0, s) f[c][s][k] = 0;
    
  }
  int ans = 0;
  rep(i, 1, s) {
    inv[i] = i > 1 ? (ll)inv[mod % i] * (mod - mod / i) % mod : 1;
    ans = (ans + (ll)f[c][0][i] * inv[i]) % mod;
  }
  ans = (ll)ans * s % mod;
  printf("%d\n", ans);
  return 0;
}